/**
 * @file
 * JavaScript for extended search form.
 */

'use strict';

(function($) {
  Drupal.behaviors.ting_extended_search = {
    attach: function (context, settings) {

      // Extended search button location.
      $('.search .collapsible .fieldset-legend > a', context).insertBefore('.search .form-submit');

      // Consider additional dom elements on header.
      if (($('#ting-extended-search-fieldset', context).length && $('#ting-search-terms-fieldset', context).length)) {
        $('section.search').addClass('search-block-form-extend-terms');
      }

      var search_input = $('.form-item-search-block-form input[name=search_block_form]', context);
      var advanced_link = $('#search-block-form a.fieldset-title', context);
      var filters_block = $('fieldset#edit-advanced');
      $('#ting-extended-search-fieldset', context).addClass('collapsed');

      if (settings.ting_extended_search.ting_extended_search_concurent_trigger !== false) {
        var actions = $('form#search-block-form .form-actions', context).find('a');
        if (actions.length !== 0) {
          actions.map(function (i, elem) {
            var content = elem.lastChild.textContent;
            content = slugify(content);
            $(elem).attr('id', content);
          });
        }
      }

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

  function slugify(text) {
    return text.toString().toLowerCase()
        .replace(/\s+/g, '-')           // Replace spaces with -
        .replace(/[^\w\-]+/g, '')       // Remove all non-word chars
        .replace(/\-\-+/g, '-')         // Replace multiple - with single -
        .replace(/^-+/, '')             // Trim - from start of text
        .replace(/-+$/, '');            // Trim - from end of text
  }

  function attachFoldOut() {
    $('.search .collapsible .fieldset-legend > a, .search .form-actions > a.fieldset-title').on('mouseenter', function() {
      $(this).click();
    });
    $('fieldset').on('mouseleave', function () {
      Drupal.toggleFieldset(this);
    });
  }

  // Extend toggleFiledset function in order to collapse other fieldsets.
  Drupal.toggleFieldset = (function(toggleFieldset){
    return function() {
      // Call original function from collapse.js
      toggleFieldset.apply(this, arguments);
      // Add collapsed class to other fieldsets.
      $('fieldset').not(arguments[0]).addClass('collapsed');
    };
  })(Drupal.toggleFieldset);

})(jQuery);
