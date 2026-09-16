"""Import the structural SysML inventory from a local OMG XMI file."""
import argparse
import hashlib
import xml.etree.ElementTree as E,json
from pathlib import Path
parser=argparse.ArgumentParser(description=__doc__)
parser.add_argument('xmi', type=Path)
parser.add_argument('--check', action='store_true')
args=parser.parse_args()
root=Path(__file__).resolve().parents[2]
X='{http://www.omg.org/spec/XMI/20161101}'
def ref(e): return e.get(X+'idref', e.get('href','')).split('#')[-1]
def bound(e,tag):
 c=e.find(tag)
 return 1 if c is None else int(c.get('value','0'))
nodes=[]
for e in E.parse(args.xmi).iter('packagedElement'):
 kind=e.get(X+'type')
 if kind not in ('uml:Class','uml:Enumeration'):continue
 ident=e.get(X+'id'); package=ident.split('-')[1]; name=e.get('name')
 n=dict(name=name,id=ident,package='usage' if package=='DefinitionAndUsage' else package.lower(),abstract=e.get('isAbstract')=='true',kind=kind.split(':')[1],bases=[ref(g.find('general')) for g in e.findall('generalization')],properties=[],literals=[l.get('name') for l in e.findall('ownedLiteral')])
 for a in e.findall('ownedAttribute'):
  default=a.find('defaultValue'); typ=ref(a.find('type'))
  p=dict(name=a.get('name'),type=typ,lower=bound(a,'lowerValue'),upper=bound(a,'upperValue'),derived=a.get('isDerived')=='true',ordered=a.get('isOrdered')=='true',unique=a.get('isUnique','true')=='true',composite=a.get('aggregation')=='composite')
  if default is not None:
   p['default']=default.get('value','false' if typ=='Boolean' else '')
   instance=default.find('instance')
   if instance is not None:p['default']=ref(instance).split('-')[-1]
  n['properties'].append(p)
 nodes.append(n)
output=json.dumps(dict(source='https://www.omg.org/spec/SysML/20250201/SysML.xmi', sha256=hashlib.sha256(args.xmi.read_bytes()).hexdigest(), types=nodes),indent=2)+'\n'
path=root/'sysml/model/abstract_syntax.json'
if args.check:
 if path.read_text()!=output: raise SystemExit('Manifest does not match XMI input')
else:
 path.write_text(output)
print(len(nodes),'types',sum(len(n['properties']) for n in nodes),'properties')
