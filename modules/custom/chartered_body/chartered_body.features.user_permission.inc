<?php
/**
 * @file
 * chartered_body.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function chartered_body_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create chartered_body content'.
  $permissions['create chartered_body content'] = array(
    'name' => 'create chartered_body content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete any chartered_body content'.
  $permissions['delete any chartered_body content'] = array(
    'name' => 'delete any chartered_body content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete own chartered_body content'.
  $permissions['delete own chartered_body content'] = array(
    'name' => 'delete own chartered_body content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit any chartered_body content'.
  $permissions['edit any chartered_body content'] = array(
    'name' => 'edit any chartered_body content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit own chartered_body content'.
  $permissions['edit own chartered_body content'] = array(
    'name' => 'edit own chartered_body content',
    'roles' => array(),
    'module' => 'node',
  );

  return $permissions;
}
