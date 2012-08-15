<?php
/**
 * @file
 * Buzzer administrative forms section
 */

/**
 * Administration form for buzzer settings.
 */
function buzzer_admin_form($form, &$form_state) {

  $form['buzzer_passcode'] = array(
    '#type' => 'textfield',
    '#required' => TRUE,
    '#title' => t('Buzzer passcode'),
    '#maxlength' => 4,
    '#maxlen' => 4,
    '#minlen' => 1,
    '#default_value' => variable_get('buzzer_passcode'),
    '#description' => t('Enter a number up to 4 digits in length'),
    '#element_validate' => array('buzzer_passcode_validate'),
  );
  $form['buzzer_command_say_request'] = array(
    '#type' => 'textfield',
    '#required' => TRUE,
    '#title' => t('Greeting response'),
    '#default_value' => variable_get('buzzer_command_say_request'),
    '#description' => t('Enter the text you would like to greet the user with'),
  );
  $form['buzzer_command_say_response'] = array(
    '#type' => 'textfield',
    '#required' => TRUE,
    '#title' => t('Response on success text'),
    '#default_value' => variable_get('buzzer_command_say_response'),
    '#description' => t('Enter the text for the response to the end user on success'),
  );
  $form['buzzer_command_say_failure'] = array(
    '#type' => 'textfield',
    '#required' => TRUE,
    '#title' => t('Response on failure text'),
    '#default_value' => variable_get('buzzer_command_say_failure'),
    '#description' => t('Enter the text for the response to the end user on failure'),
  );
  $form['buzzer_dtmf'] = array(
    '#type' => 'select',
    '#required' => TRUE,
    '#title' => t('DTMF Tone'),
    '#options' => array(0, 1, 2, 3, 4, 5, 6, 7, 8, 9),
    '#default_value' => variable_get('buzzer_dtmf'),
    '#description' => t('The DTMF tone to generate uppon success'),
  );
  return system_settings_form($form);
}

/**
 * Element validator for the buzzer code.
 */
function buzzer_passcode_validate($element, &$form_state, $form) {
  if (!is_numeric($element['#value']) || strlen($element['#value']) > 4) {
    form_error($element, t('Buzzer code must be a number up to 4 digits in length'));
  }
}
