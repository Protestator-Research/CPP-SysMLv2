#!/bin/bash
# cibuildwheel (Linux): runs ONCE per container (manylinux_2_28), before the wheel is built.
# Installs Conan, configures the private remote (only if ARTIFACTORY_URL is passed in), restores/saves the Conan package cache
# through the host file system (/host = host root, cibuildwheel's docker engine) and installs the static dependencies into the fixed
# folder /project/build-python/conan. pyproject.toml ([tool.cibuildwheel.linux].environment) points CMAKE_TOOLCHAIN_FILE there.
set -euo pipefail

cd /project
PYBIN=/opt/python/cp312-cp312/bin
"$PYBIN/python" -m pip install --quiet conan
export PATH="$PYBIN:$PATH"

# host directory of the cache (created by the workflow, the same path is cached by actions/cache); optional
CACHE_FILE="/host${CONAN_CACHE_HOST_DIR:-/nonexistent}/conan-cache.tgz"
export CONAN_HOME=/root/.conan2

conan profile detect --force
if [ -n "${ARTIFACTORY_URL:-}" ]; then
  conan remote add --force protestator-conan "$ARTIFACTORY_URL"
  conan remote login -p "$ARTIFACTORY_TOKEN" protestator-conan "$ARTIFACTORY_USER"
  conan remote remove conancenter
fi

if [ -f "$CACHE_FILE" ]; then
  conan cache restore "$CACHE_FILE" || echo "conan cache restore failed, continuing without cache"
fi

python python/tools/conan_deps.py --output-folder /project/build-python/conan --format json >/dev/null

if [ -d "$(dirname "$CACHE_FILE")" ] && [ "${CONAN_CACHE_HIT:-}" != true ]; then
  rm -f "$CACHE_FILE"
  conan cache save "*/*:*" --file "$CACHE_FILE" || echo "conan cache save failed, continuing"
  chmod a+r "$CACHE_FILE" 2>/dev/null || true
fi
