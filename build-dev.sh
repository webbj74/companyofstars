#!/bin/sh

MAKEFILE='build-companyofstars.make'
TARGET=$1
CALLPATH=`dirname $0`
HTTP_PORT=8080
MYSQL_PORT=33066
MYSQL_HOST=127.0.0.1
MYSQL_USER=root
MYSQL_PASS=root123
DRUPAL_USER=admin
DRUPAL_PASS=admin123

# Remove target directory if it exists.
if [[ -d "${TARGET}" ]]; then
  chmod -R +w "${TARGET}" && rm -rf "${TARGET}"
fi

# Build site
drush make --working-copy --concurrency=5 "${CALLPATH}/${MAKEFILE}" "${TARGET}"

if [[ -d "${TARGET}" ]]; then
  cd "${TARGET}"
  drush si companyofstars --db-url=mysql://${MYSQL_USER}:${MYSQL_PASS}@${MYSQL_HOST}:${MYSQL_PORT}/drupal --account-name=${DRUPAL_USER} --account-pass=${DRUPAL_PASS} --account-mail=admin@example.com --site-mail=noreply@example.com --yes
fi

