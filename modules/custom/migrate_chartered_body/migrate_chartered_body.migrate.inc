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
        'source_file' => __DIR__ . '/data/company-of-stars.json',
        'group_name' => 'chartered_body',
      ),
      'CharteredBodyEvents' => array(
        'class_name' => 'CharteredBodyEventMigration',
        'source_file' => __DIR__ . '/data/company-of-stars.json',
        'group_name' => 'chartered_body',
      ),
    ),
  );
  return $api;
}
