<?php
/**
 * @file
 * chartered_body.features.inc
 */

/**
 * Implements hook_node_info().
 */
function chartered_body_node_info() {
  $items = array(
    'chartered_body' => array(
      'name' => t('Chartered Body'),
      'base' => 'node_content',
      'description' => t('Add a new chartered body to the Company of Stars. Update the history of an existing body by editing the node itself.'),
      'has_title' => '1',
      'title_label' => t('Chartered Name'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
