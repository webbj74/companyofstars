<?php

/**
 * @file
 * Enables modules and site configuration for Company of Stars site installation.
 */

/**
 * Implements hook_permission().
 */
function companyofstars_permission() {
  return array(
    'companyofstars admin' => array(
      'title' => t('Administer Company of Stars'),
      'description' => t('Perform administration tasks for Company of Stars.'),
    ),
  );
}

/**
 * Implements hook_form_FORM_ID_alter() for install_configure_form().
 *
 * Allows the profile to alter the site configuration form.
 */
function companyofstars_form_install_configure_form_alter(&$form, $form_state) {
  // Pre-populate the site name with the server name.
  $form['site_information']['site_name']['#default_value'] = "In the Company of Stars";
}

