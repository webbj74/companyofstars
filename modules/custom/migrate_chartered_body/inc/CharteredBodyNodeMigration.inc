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
      ['reader_class' => 'CharteredBodyNodeMigrationJSONReader']
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
For early bodies (1980-1988) where no exact closing date is available, Terry has used the last month that the body was listed in The Link as the closing date.  Since the listings in The Link were consider the official list of active bodies, a removal of the body is the closest to an official date available.  Likewise, a body’s appearance on this list was sometimes used as an opening date when no other date was available.  If you happen to find an error or omission on the list, or can provide more accurate information than please contact me at (email-redacted)

Data in this revision was compiled by Terry Murdock and completed on 6/1/2012.  Any errors, or shocking factual oversteps are his alone.  Invaluable assistance in finding source material or other assistance was provided by Mike Kolson, Richard Kaczynski, and Scott Wilder.  Special thanks are owed to Bill Heidrick, who answered my numerous messages with wit and a wealth of information.
EOT;
    $this->addFieldMapping('title', 'body_name');
    $this->addFieldMapping('body', 'notes');

    $this->addFieldMapping('field_chartered_date:year', 'date_chartered_y');
    $this->addFieldMapping('field_chartered_date:month', 'date_chartered_m');
    $this->addFieldMapping('field_chartered_date:day', 'date_chartered_d');

    $this->addFieldMapping('field_dissolved_date:year', 'date_dissolved_y');
    $this->addFieldMapping('field_dissolved_date:month', 'date_dissolved_m');
    $this->addFieldMapping('field_dissolved_date:day', 'date_dissolved_d');


    $this->addFieldMapping('log')->defaultValue("TEST");
    $this->addFieldMapping('revision')->defaultValue(1);
  }

  public function prepare_row($row) {
    $row->date_chartered_y = '2001';
    $row->date_chartered_m = '01';
    $row->date_chartered_d = '02';
    $row->date_dissolved_y = '2002';
    $row->date_dissolved_m = '03';
    $row->date_dissolved_d = null;
  }

  public function fields() {
    return [
      'date_chartered' => 'original date this body opened',
      'date_dissolved' => 'final date this body closed',
    ];
  }

}
