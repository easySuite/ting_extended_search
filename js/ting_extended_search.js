/**
 * @file
 * JavaScript for extended search form.
 */

'use strict';

(function($) {
  Drupal.behaviors.ting_extended_search = {
    attach: function (context) {

      // Extended search button location.
      $('.search .collapsible .fieldset-legend > a', context).insertBefore('.search .form-submit');

      // Consider additional dom elements on header.
      if (!($('.form-item-ting-field-search', context).length && $('div.ding-user-header', context).length) && $('#ting-search-terms-fieldset', context).length) {
        $('#search-radios').addClass('two-radio-button');
      }

      var search_input = $('.form-item-search-block-form input[name=search_block_form]', context);
      var advanced_link = $('#search-block-form a.fieldset-title', context);
      var filters_block = $('fieldset#edit-advanced');
      $('#ting-extended-search-fieldset', context).addClass('collapsed');

      // Default states.
      advanced_link.addClass('closed');
      filters_block.addClass('collapsed');
      search_input.focus();

      // If display of advanced search is disabled in backend for search results
      // page, we are not displaying this.
      var display_on_search = Drupal.settings.ting_extended_search["ting_extended_search_search_result"];
      if ((display_on_search === 0) && ($(document).find('body').hasClass('page-search') !== false)) {
        filters_block.remove();
        advanced_link.remove();

        return;
      }

      var foldout = Drupal.settings.ting_extended_search["ting_extended_search_foldout_event"];
      if (foldout) {
        attachFoldOut();
      }
    }
  };

  function attachFoldOut() {
    $('.search .collapsible .fieldset-legend > a, .search .form-actions > a.fieldset-title').on('mouseenter', function() {
      $('.search .form-actions > a.fieldset-title').click();
      $('.search .form-actions > a.fieldset-title').removeClass('closed');
      $('.search .form-actions > a.fieldset-title').addClass('opened');
    });
    $('#edit-advanced').on('mouseleave', function () {
      $('.search .form-actions > a.fieldset-title').click();
      $('.search .form-actions > a.fieldset-title').addClass('closed');
      $('.search .form-actions > a.fieldset-title').removeClass('opened');
    });
  }
})(jQuery);
