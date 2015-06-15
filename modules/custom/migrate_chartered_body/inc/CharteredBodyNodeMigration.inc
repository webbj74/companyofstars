<?php

class CharteredBodyNodeMigrationJSONReader extends MigrateJSONReader {
  /**
   * Implementation of Iterator::next().
   *
   * Populates currentElement (the object being retrieved) and currentId (that
   * object's unique identifier) from the specified JSON file. Sets both to
   * NULL at end-of-file. Handles properly-formed JSON, as well as some improper
   * coding (specifically that generated in Ning exports).
   *
   * @return void
   */
  public function next() {
    migrate_instrument_start('MigrateJSONReader::next');

    $this->currentElement = $this->currentId = NULL;

    // Open the file and position it if necessary
    if (!$this->fileHandle) {
      $this->fileHandle = fopen($this->url, 'r');
      if (!$this->fileHandle) {
        Migration::displayMessage(t('Could not open JSON file !url',
          array('!url' => $this->url)));
        return;
      }

      // We're expecting an associative array, so the first character should be {.
      $char = $this->getNonBlank();
      // Ning exports are wrapped in bogus (), so skip a leading (
      if ($char == '(') {
        $char = $this->getNonBlank();
      }
      if ($char != '{') {
        Migration::displayMessage(t('!url is not a JSON file containing an associative array of objects [' . $char . ']',
          array('!url' => $this->url)));
        return;
      }
    }

    // We expect to be positioned either at an object (beginning with {) or
    // the end of the file (we should see a ] indicating this). Or, an
    // object-separating comma, to be skipped. Note that this treats
    // commas as optional between objects, which helps with processing
    // malformed JSON with missing commas (as in Ning exports).
    $c = $this->getNonBlank();
    if ($c == ',') {
      $c = $this->getNonBlank();
    }
    // Ning sometimes emits a ] where there should be a comma.
    elseif ($c == '}') {
      $c = $this->getNonBlank();
      if ($c != '{') {
        $c = NULL;
      }
    }

    if ($c) {
      // body_name, the id
      $id = '';
      if ($c == '"') {
        $in_string = TRUE;
        $in_escape = FALSE;
        while (($c = fgetc($this->fileHandle)) !== FALSE) {

          if ($in_string) {
            // Quietly accept an escaped character
            if ($in_escape) {
              $in_escape = FALSE;
              $id .= $c;
            }
            else {
              switch ($c) {
                // Unescaped " means end of string
                case '"':
                  $in_string = FALSE;
                  break;
                // Unescaped \\ means start of escape
                case '\\':
                  $id .= $c;
                  $in_escape = TRUE;
                  break;
                default:
                  $id .= $c;
                  break;
              }
            }
          }
          if (!$in_string) {
            break;
          }
        }

        if (!$id) {
          Migration::displayMessage(t('found null id [' . $id . ']', array()));
          return;
        }
        $this->currentId = $id;
      }

      // ffwd to value
      $c = $this->getNonBlank();
      if ($c != ':') {
        Migration::displayMessage(t('associative op not following [' . $id . ']', array()));
        return;
      }
      $c = $this->getNonBlank();
    }


    // We expect to be at the first character of an object now.
    if ($c == '{') {
      // Start building a JSON string for this object.
      $json = $c;
      // Look for the closing }, ignoring brackets in strings, tracking nested
      // brackets. Watch out for escaped quotes, but also note that \\" is not
      // an escaped quote.
      $depth = 1;
      $in_string = FALSE;
      $in_escape = FALSE;
      while (($c = fgetc($this->fileHandle)) !== FALSE) {
        $json .= $c;
        if ($in_string) {
          // Quietly accept an escaped character
          if ($in_escape) {
            $in_escape = FALSE;
          }
          else {
            switch ($c) {
              // Unescaped " means end of string
              case '"':
                $in_string = FALSE;
                break;
              // Unescaped \\ means start of escape
              case '\\':
                $in_escape = TRUE;
                break;
            }
          }
        }
        else {
          // Outside of strings, recognize {} as depth changes, " as start of
          // string.
          switch ($c) {
            case '{':
              $depth++;
              break;
            case '}':
              $depth--;
              break;
            case '"':
              $in_string = TRUE;
              break;
          }
          // We've found our match, exit the loop.
          if ($depth < 1) {
            break;
          }
        }
      }

      // Turn the JSON string into an object.
      $this->currentElement = json_decode($json);
      $this->currentElement->body_name = $this->currentId;
    }
    else {
      $this->currentElement = NULL;
      $this->currentId = NULL;
    }
    migrate_instrument_stop('MigrateJSONReader::next');
  }
}

class CharteredBodyNodeMigration extends Migration {
  public function __construct($arguments) {
    parent::__construct($arguments);

    // Create a MigrateSource object, which manages retrieving the input data.
    $this->source = new MigrateSourceJSON(
      $arguments['source_file'],
      'body_name',
      $this->fields(),
      [] // ['reader_class' => 'CharteredBodyNodeMigrationJSONReader']
    );
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

    $log = <<<EOT
This list was compiled by Terry Murdock and completed on 6/1/2012. Any errors, or shocking factual oversteps are his alone. Invaluable assistance in finding source material or other assistance was provided by Mike Kolson, Richard Kaczynski, and Scott Wilder.  Special thanks are owed to Bill Heidrick, who answered Terry's numerous messages with wit and a wealth of information.

For early bodies (1980-1988) where no exact closing date is available, Terry used the last month that the body was listed in The Link as the closing date.  Since the listings in The Link were consider the official list of active bodies, a removal of the body is the closest to an official date available.  Likewise, a body’s appearance on this list was sometimes used as an opening date when no other date was available.  If you happen to find an error or omission on the list, or can provide more accurate information than please contact us.
EOT;
    $this->addFieldMapping('title', 'body_name');
    $this->addFieldMapping('field_current_status', 'last_status');
    $this->addFieldMapping('body', 'notes');
    $this->addFieldMapping('field_references', 'references')->separator(';');
    $this->addFieldMapping('uid', NULL)->defaultValue(1);

    $this->addFieldMapping('log')->defaultValue($log);
    $this->addFieldMapping('revision')->defaultValue(1);
    $this->addFieldMapping('revision_uid')->defaultValue(1);

    // Unmapped destination fields
    // Some conventions we use here: with a long list of fields to ignore, we
    // arrange them alphabetically, one distinct field per line (although
    // subfields of the same field may be grouped on the same line), and indent
    // subfields to distinguish them from top-level fields.
    $this->addUnmigratedDestinations(array(
        'body:format',
        'body:language',
        'body:summary',
      'changed',
      'comment',
      'created',
      'field_event_history',
        'field_event_history:revision_id',
        'field_references:language',
      'is_new',
      'language',
      'nid',
      'promote',
//      'revision_uid',
      'status',
      'sticky',
      'tnid',
      'translate',
    ));

  }

  /*
  public function import(stdClass $node, stdClass $row) {
    // We're importing revisions, this should be set.
    $node->revision = 1;

    if (empty($node->nid)) {
      throw new MigrateException(t('Missing incoming nid.'));
    }

    return parent::import($node, $row);
  }
  */

  public function prepareRow($row) {
    if (isset($row->last_status) && $row->last_status == 'Dissolved') {
      $row->last_status = 'Closed';
    }
    if (isset($row->references) && is_array($row->references)) {
      $row->references = implode(';', $row->references);
    }
  }

  public function fields() {
    return [
      'body_name' => 'unique name of body',
      'last_status' => 'last_status',
      'notes' => 'notes',
      'references' => 'references',
      'status_note' => 'status_note',
    ];
  }

}
