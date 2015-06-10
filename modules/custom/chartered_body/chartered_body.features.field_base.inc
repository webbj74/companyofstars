<?php
/**
 * @file
 * chartered_body.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function chartered_body_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'body'
  $field_bases['body'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(
      0 => 'node',
    ),
    'field_name' => 'body',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(),
    'translatable' => 0,
    'type' => 'text_with_summary',
  );

  // Exported field_base: 'field_body_status_changes'
  $field_bases['field_body_status_changes'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_body_status_changes',
    'indexes' => array(
      'revision_id' => array(
        0 => 'revision_id',
      ),
    ),
    'locked' => 0,
    'module' => 'field_collection',
    'settings' => array(
      'hide_blank_items' => 1,
      'path' => '',
    ),
    'translatable' => 0,
    'type' => 'field_collection',
  );

  // Exported field_base: 'field_chartered_date'
  $field_bases['field_chartered_date'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_chartered_date',
    'indexes' => array(
      'timestamp' => array(
        0 => 'timestamp',
      ),
    ),
    'locked' => 0,
    'module' => 'partial_date',
    'settings' => array(
      'estimates' => array(
        'day' => array(
          '0|12' => 'The start of the month',
          '10|20' => 'The middle of the month',
          '18|31' => 'The end of the month',
        ),
        'hour' => array(
          '0|1' => 'Midnight',
          '6|12' => 'Morning',
          '6|18' => 'Day time',
          '12|13' => 'Noon',
          '12|18' => 'Afternoon',
          '18|6' => 'Night',
          '18|22' => 'Evening',
        ),
        'minute' => array(),
        'month' => array(
          '2|4' => 'Spring',
          '5|7' => 'Summer',
          '8|10' => 'Autumn',
          '11|1' => 'Winter',
        ),
        'second' => array(),
        'year' => array(
          '1890|1899' => '19th century',
          '1900|1999' => '20th century',
          '2000|2099' => '21st century',
        ),
      ),
      'minimum_components' => array(
        'from_estimates_day' => 0,
        'from_estimates_hour' => 0,
        'from_estimates_minute' => 0,
        'from_estimates_month' => 0,
        'from_estimates_second' => 0,
        'from_estimates_year' => 0,
        'from_granularity_day' => 0,
        'from_granularity_hour' => 0,
        'from_granularity_minute' => 0,
        'from_granularity_month' => 0,
        'from_granularity_second' => 0,
        'from_granularity_timezone' => 0,
        'from_granularity_year' => 1,
        'txt_long' => 0,
        'txt_short' => 0,
      ),
    ),
    'translatable' => 0,
    'type' => 'partial_date',
  );

  // Exported field_base: 'field_dissolved_date'
  $field_bases['field_dissolved_date'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_dissolved_date',
    'indexes' => array(
      'timestamp' => array(
        0 => 'timestamp',
      ),
    ),
    'locked' => 0,
    'module' => 'partial_date',
    'settings' => array(
      'estimates' => array(
        'day' => array(
          '0|12' => 'The start of the month',
          '10|20' => 'The middle of the month',
          '18|31' => 'The end of the month',
        ),
        'hour' => array(
          '0|1' => 'Midnight',
          '6|12' => 'Morning',
          '6|18' => 'Day time',
          '12|13' => 'Noon',
          '12|18' => 'Afternoon',
          '18|6' => 'Night',
          '18|22' => 'Evening',
        ),
        'minute' => array(),
        'month' => array(
          '2|4' => 'Spring',
          '5|7' => 'Summer',
          '8|10' => 'Autumn',
          '11|1' => 'Winter',
        ),
        'second' => array(),
        'year' => array(
          '1890|1899' => '19th century',
          '1900|1999' => '20th century',
          '2000|2099' => '21st century',
        ),
      ),
      'minimum_components' => array(
        'from_estimates_day' => 0,
        'from_estimates_hour' => 0,
        'from_estimates_minute' => 0,
        'from_estimates_month' => 0,
        'from_estimates_second' => 0,
        'from_estimates_year' => 0,
        'from_granularity_day' => 0,
        'from_granularity_hour' => 0,
        'from_granularity_minute' => 0,
        'from_granularity_month' => 0,
        'from_granularity_second' => 0,
        'from_granularity_timezone' => 0,
        'from_granularity_year' => 1,
        'txt_long' => 0,
        'txt_short' => 0,
      ),
    ),
    'translatable' => 0,
    'type' => 'partial_date',
  );

  // Exported field_base: 'field_new_city'
  $field_bases['field_new_city'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_new_city',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  // Exported field_base: 'field_new_country'
  $field_bases['field_new_country'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_new_country',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  // Exported field_base: 'field_new_date'
  $field_bases['field_new_date'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_new_date',
    'indexes' => array(
      'timestamp' => array(
        0 => 'timestamp',
      ),
    ),
    'locked' => 0,
    'module' => 'partial_date',
    'settings' => array(
      'estimates' => array(
        'day' => array(
          '0|12' => 'The start of the month',
          '10|20' => 'The middle of the month',
          '18|31' => 'The end of the month',
        ),
        'hour' => array(
          '0|1' => 'Midnight',
          '6|12' => 'Morning',
          '6|18' => 'Day time',
          '12|13' => 'Noon',
          '12|18' => 'Afternoon',
          '18|6' => 'Night',
          '18|22' => 'Evening',
        ),
        'minute' => array(),
        'month' => array(
          '2|4' => 'Spring',
          '5|7' => 'Summer',
          '8|10' => 'Autumn',
          '11|1' => 'Winter',
        ),
        'second' => array(),
        'year' => array(
          '1890|1899' => '19th century',
          '1900|1999' => '20th century',
          '2000|2099' => '21st century',
        ),
      ),
      'minimum_components' => array(
        'from_estimates_day' => 0,
        'from_estimates_hour' => 0,
        'from_estimates_minute' => 0,
        'from_estimates_month' => 0,
        'from_estimates_second' => 0,
        'from_estimates_year' => 0,
        'from_granularity_day' => 0,
        'from_granularity_hour' => 0,
        'from_granularity_minute' => 0,
        'from_granularity_month' => 0,
        'from_granularity_second' => 0,
        'from_granularity_timezone' => 0,
        'from_granularity_year' => 1,
        'txt_long' => 0,
        'txt_short' => 0,
      ),
    ),
    'translatable' => 0,
    'type' => 'partial_date',
  );

  // Exported field_base: 'field_new_reference'
  $field_bases['field_new_reference'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_new_reference',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  // Exported field_base: 'field_new_region'
  $field_bases['field_new_region'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_new_region',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  // Exported field_base: 'field_new_type'
  $field_bases['field_new_type'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_new_type',
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        'Chartered as Camp' => 'Chartered as Camp',
        'Rechartered as Camp' => 'Rechartered as Camp',
        'Rechartered as Oasis' => 'Rechartered as Oasis',
        'Rechartered as Lodge' => 'Rechartered as Lodge',
        'Moved Location' => 'Moved Location',
        'Dissolved' => 'Dissolved',
      ),
      'allowed_values_function' => '',
    ),
    'translatable' => 0,
    'type' => 'list_text',
  );

  return $field_bases;
}
