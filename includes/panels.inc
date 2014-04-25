<?php

/**
 * @file panels.inc
 */

/**
 * Helper function to render a mini-panel. Shamelessly copied from Panels to
 * wrap into a convenient function.
 *
 * @param  [string] $identifier
 *   Machine-name for the mini-panel you want to render.
 *
 * @return
 *   A string of markup representing the mini-panel.
 */
function hap_panels_mini_render($identifier) {
  // We don't have a hard dependency on Panels, so drop out if Panels is not
  // available.
  if (!module_exists('panels')) {
    return;
  }

  $mini = panels_mini_load($identifier);
  if (empty($mini)) {
    // No panel for you!!
    return;
  }

  // Pass along Page Manager contexts, if they exist.
  ctools_include('context');

  $contexts = array();
  if (module_exists('page_manager') && $current_page = page_manager_get_current_page()) {
    if (!empty($current_page['contexts'])) {
      $contexts = ctools_context_match_required_contexts($mini->requiredcontexts, $current_page['contexts']);
    }
  }

  $mini->context = $mini->display->context =  ctools_context_load_contexts($mini, FALSE, $contexts);
  $mini->display->css_id = panels_mini_get_id($mini->name);

  return panels_render_display($mini->display);
}
