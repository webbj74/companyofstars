<?php

class CharteredBodyNodeMigration extends Migration {
  public function __construct($arguments) {
    parent::__construct($arguments);

    // Create a MigrateSource object, which manages retrieving the input data.
    $this->source = new MigrateSourceCSV($arguments['source_file'], $this->csvcolumns());
    $this->destination = new MigrateDestinationNode('chartered_body');

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'body_name' => array(
          'type' => 'varchar',
          'length' => 255,
          'not null' => TRUE,
          'description' => 'Body name',
        )
      ),
      MigrateDestinationNode::getKeySchema()
    );

    $this->addFieldMapping('title', 'body_name');
    $this->addFieldMapping('body', 'notes');
    $this->addFieldMapping('field_chartered_date', 'chartered_date');
    $this->addFieldMapping('field_dissolved_date', 'dissolved_date');
  }

  protected function csvcolumns() {
    $columns[0] = array('body_name', 'Name of Body');
    $columns[1] = array('location_note', 'Location Notes');
    $columns[2] = array('chartered_date', 'Chartered Date');
    $columns[3] = array('dissolved_date', 'Dissolved Date');
    $columns[4] = array('notes', 'Notes');
    $columns[5] = array('references', 'References');
    return $columns;
  }
}
