<?php

class CharteredBodyEventMigration extends Migration {
  public function __construct($arguments) {
    parent::__construct($arguments);

    $this->description = t('Event History field migration from JSON source.');
    $this->dependencies = array('CharteredBodyNodes');

    $this->source = new MigrateSourceJSON(
      $arguments['source_file'],
      'body_name',
      $this->fields(),
      [] //['reader_class' => 'CharteredBodyNodeMigrationJSONReader']
    );

    $this->destination = new MigrateDestinationFieldCollection(
      'field_event_history',
      array('host_entity_type' => 'node')
    );

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'key' => array(
          'type' => 'varchar',
          'length' => 255,
          'not null' => TRUE,
          'description' => 'Body name plus ID',
        ),
      ),
      MigrateDestinationFieldCollection::getKeySchema()
    );

    $this->addFieldMapping('host_entity_id', 'body_name')->sourceMigration('CharteredBodyNodes');

    $this->addFieldMapping('field_event_type', 'event');
    $this->addFieldMapping('field_event_date', 'date');
    $this->addFieldMapping('field_event_body_name', 'name');
    $this->addFieldMapping('field_event_body_type', 'type');
    $this->addFieldMapping('field_event_city', 'city');
    $this->addFieldMapping('field_event_region', 'state');
    $this->addFieldMapping('field_event_country')->defaultValue('United States of America');
  }

  public function prepareRow($row) {

  }

  public function fields() {
    return [
      'event' => 'type',
      'date' => 'date',
      'name' => 'name',
      'type' => 'type',
      'city' => 'city',
      'state' => 'state',
      'body_name' => 'body_name',
      'key' => 'unique id',
    ];
  }
}
