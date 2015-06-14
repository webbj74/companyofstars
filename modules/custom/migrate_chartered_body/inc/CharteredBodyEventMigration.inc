<?php

class CharteredBodyEventMigration extends Migration {
  public function __construct($arguments) {
    parent::__construct($arguments);

    $this->description = t('Event History field migration from JSON source.');
    $this->dependencies = array('CharteredBodyNodes');

    $columns = array(
      array('id', 'Source ID'),
      array('article', 'Article ID'),
      array('field_title', 'Title'),
      array('field_length', 'Length'),
    );

    /*
    $this->source = new MigrateSourceCSV(
      drupal_get_path('module', 'fc_migration') . '/data/albums.csv',
      $columns,
      array('header_rows' => 1)
    );*/
    $this->source = new MigrateSourceJSON(
      $arguments['source_file'],
      'body_name',
      $this->fields(),
      ['reader_class' => 'CharteredBodyNodeMigrationJSONReader']
    );

    $this->destination = new MigrateDestinationFieldCollection(
      'field_event_history',
      array('host_entity_type' => 'node')
    );

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'event' => array(
          'type' => 'varchar',
          'length' => 255,
          'not null' => TRUE,
          'description' => 'Body name',
        ),
      ),
      MigrateDestinationFieldCollection::getKeySchema()
    );

    $this->addFieldMapping('host_entity_id', 'body_name')->sourceMigration('CharteredBodyNodes');

    $this->addFieldMapping('field_event_type', 'event_type');
    $this->addFieldMapping('field_event_body_name', 'body_name');
    $this->addFieldMapping('field_event_body_type', 'body_type');
    $this->addFieldMapping('field_event_city', 'event_city');
    $this->addFieldMapping('field_event_region', 'event_state');
    $this->addFieldMapping('field_event_country')->defaultValue('United States of America');
  }

  public function prepareRow($row) {
    if(isset($row->status_updates)) {
      $row->event = sprintf("%s-%02d", $row->body_name, 0);
      $row->event_type = $row->status_updates[0]->event;
      $row->event_date = $row->status_updates[0]->date;
      $row->body_name = $row->status_updates[0]->name;
      $row->body_type = $row->status_updates[0]->type;
      $row->event_city = $row->status_updates[0]->city;
      $row->event_state = $row->status_updates[0]->state;
    }
  }

  public function fields() {
    return [
      'event_type' => 'type',
      'event_date' => 'date',
      'body_name' => 'name',
      'body_type' => 'type',
      'event_city' => 'city',
      'event_state' => 'state',
    ];
  }
}
