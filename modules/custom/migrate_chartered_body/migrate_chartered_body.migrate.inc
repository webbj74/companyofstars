<?php

/**
 * @file
 *   Importer for Chartered Body Data
 */

/*
 * Implements hook_migrate_api() for APIv2.
 */
function migrate_chartered_body_migrate_api() {
  $api = array(
    'api' => 2,
    'groups' => array(
      'chartered_body' => array(
        'title' => t('Chartered Bodies'),
      ),
    ),
    'migrations' => array(
      'CharteredBodyNodes' => array(
        'class_name' => 'CharteredBodyNodeMigration',
        'source_file' => '/tmp/cos.csv',
        'group_name' => 'chartered_body',
      ),
    ),
  );
  return $api;
}
