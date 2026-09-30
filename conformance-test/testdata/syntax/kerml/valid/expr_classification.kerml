// expect: valid
package ClassificationExpressions {
    feature isSensor = x istype Sensor;
    feature hasSensorType = x hastype Sensor;
    feature classified = x @ Sensor;
    feature cast = x as Sensor;
    feature castChain = (x as Sensor).reading;
    feature combined = x istype Sensor == true;
    feature offset = a + 1 hastype Length;
    feature metaTest = designModel @@ ApprovalAnnotation;
    feature metaCast = sensors meta KerML::Feature;
    feature implicitSelf = istype Sensor;
    feature implicitAt = @Sensor;
    feature everything = all Sensor;
    filter @Safety or @Security;
}
