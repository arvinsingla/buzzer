<?php
/**
 * @file
 * Buzzer administrative forms section
 */

/**
 * Administration form for buzzer settings.
 */
function buzzer_admin_form($form, &$form_state) {

  $form['buzzer_mode'] = array(
    '#type' => 'select',
    '#required' => TRUE,
    '#title' => t('Buzzer mode'),
    '#options' => array(
      'none' => t('No code (automatic entry)'),
      'global' => t('Global code'),
      'user' => t('User codes'),
    ),
    '#default_value' => variable_get('buzzer_mode'),
    '#description' => t('Select the authentication mode you would like buzzer to operate on'),
  );

  $form['buzzer_code'] = array(
    '#type' => 'textfield',
    '#title' => t('Global buzzer passcode'),
    '#maxlength' => 4,
    '#maxlen' => 4,
    '#minlen' => 1,
    '#default_value' => variable_get('buzzer_code'),
    '#description' => t('Enter a number up to 4 digits in length'),
    '#states' => array(
      'visible' => array(
        '#edit-buzzer-mode' => array(
          'value' => 'global'
        )
      ),
      'required' => array(
        '#edit-buzzer-mode' => array(
          'value' => 'global'
        )
      ),
    ),
  );

  $form['buzzer_command_say_userid'] = array(
    '#type' => 'textfield',
    '#title' => t('User id request'),
    '#default_value' => variable_get('buzzer_command_say_userid'),
    '#description' => t('Enter the text to instruct the user for their user id'),
    '#states' => array(
      'visible' => array(
        '#edit-buzzer-mode' => array(
          'value' => 'user'
        )
      ),
      'required' => array(
        '#edit-buzzer-mode' => array(
          'value' => 'user'
        )
      ),
    ),
  );

  $form['buzzer_command_say_password'] = array(
    '#type' => 'textfield',
    '#required' => TRUE,
    '#title' => t('Password request'),
    '#default_value' => variable_get('buzzer_command_say_password'),
    '#description' => t('Enter the text to instruct the user for their password'),
    '#states' => array(
      'invisible' => array(
        '#edit-buzzer-mode' => array(
          'value' => 'none'
        )
      ),
    ),
  );
  $form['buzzer_command_say_confirmation'] = array(
    '#type' => 'textfield',
    '#required' => TRUE,
    '#title' => t('Response on success'),
    '#default_value' => variable_get('buzzer_command_say_confirmation'),
    '#description' => t('Enter the text to confirm success'),
    '#states' => array(
      'invisible' => array(
        '#edit-buzzer-mode' => array(
          'value' => 'none'
        )
      ),
    ),
  );
  $form['buzzer_command_say_failure'] = array(
    '#type' => 'textfield',
    '#required' => TRUE,
    '#title' => t('Response on failure'),
    '#default_value' => variable_get('buzzer_command_say_failure'),
    '#description' => t('Enter the text for a failure response'),
    '#states' => array(
      'invisible' => array(
        '#edit-buzzer-mode' => array(
          'value' => 'none'
        )
      ),
    ),
  );
  $form['buzzer_dtmf'] = array(
    '#type' => 'select',
    '#required' => TRUE,
    '#title' => t('DTMF Tone'),
    '#options' => array(0, 1, 2, 3, 4, 5, 6, 7, 8, 9),
    '#default_value' => variable_get('buzzer_dtmf'),
    '#description' => t('The DTMF tone to generate uppon success'),
  );
  
  $form['buzzer_sms'] = array(
    '#type' => 'checkbox', 
    '#title' => t('Send text message'),
    '#default_value' => variable_get('buzzer_sms'),
    '#description' => t('Send a text message to a specified number when someone enters'),
  );
  
  $form['buzzer_sms_number'] = array(
    '#type' => 'textfield',
    '#required' => TRUE,
    '#title' => t('Number'),
    '#default_value' => variable_get('buzzer_sms_number'),
    '#description' => t('Enter a phone number'),
    '#element_validate' => array('buzzer_sms_number_validate'),
    '#states' => array(
      'invisible' => array(
        ':input[name="buzzer_sms"]' => array('checked' => FALSE),
      ),
    ),
  );
  
  return system_settings_form($form);
}

/**
 * Element validator for the phone number field.
 */
function buzzer_sms_number_validate($element, &$form_state, $form) {
  if ($number = twilio_validate_number($element['#value'], FALSE)) {
    $form_state['values']['twilio_number'] = $number;
  }
  else {
    form_error($element, t('You must enter a valid 10 digit phone number'));
  }
}

/**
 * Validation function for the buzzer_admin_form.
 */
function buzzer_admin_form_validate($form, &$form_state) {
  $values = $form_state['values'];
  switch ($values['buzzer_mode']) {
    case 'global':{
      if (empty($values['buzzer_code']) || !is_numeric($values['buzzer_code']) || strlen($values['buzzer_code']) > 4) {
        form_set_error('buzzer_code', t('Buzzer code must be a number up to 4 digits in length'));
      }
      break;
    }
    case 'user':{
      if (empty($values['buzzer_command_say_userid'])) {
        form_set_error('buzzer_command_say_userid', t('User id request field is required'));
      }
      break;
    }
  }
}
