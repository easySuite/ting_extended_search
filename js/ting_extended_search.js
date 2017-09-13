/**
 * @file
 * JavaScript for extended search form.
 */

(function($) {
  Drupal.behaviors.clearExtendForm = {
    attach:function(context, settings) {
      $('#extend-form-clear', context).click(function() {
        $("#edit-language").val('');
        $("#edit-type").val('');
        $("#edit-source").val('');
        $("#edit-creator").val('');
        $("#edit-title").val('');
        $("#edit-subject").val('');
        $("#edit-search-block-form--2").val('');
        return false;
      });
      attachFoldOut();
    }
  };

  Drupal.extendedQueryDisplay = function() {
    var queryText = $("input").filter("[name='search_block_form']").val();
    var parts = [];
    if (queryText) {
      parts.push(queryText);
    }
    var val;
    var label;
    $('#edit-advanced .form-item').each(function (i, elem) {
      var $val = $('input,select', elem).val();
      var $label = label = $('label', elem).text();
      if (($val) && ($label)) {
        parts.push(label + " = " + val);
      }
    });

    if (parts.length > 0) {
      $('#search-query-string').text(parts.join(Drupal.t(" AND ")));
    }
  };
  
  $(function () {
    // Extended search button location.
    $('#edit-advanced a.fieldset-title').addClass( "extend-search" );
    $('.search #edit-advanced .fieldset-legend > a.extend-search').insertBefore('.site-header .search .form-submit');

    attachFoldOut();

    var linkIsClicked = false;
    $('input.auto-submit').focus(function() {
      $('a.fieldset-title').css('visibility', 'visible');
    });

    $('.form-actions a.fieldset-title').mousedown(function() {
      // $('input.auto-submit').focus();
      linkIsClicked = true;
    });

    $('input.auto-submit').on('blur', function(event) {
      if(linkIsClicked) {
        event.stopImmediatePropagation();
        event.preventDefault();
        $('input.auto-submit').focus();
        linkIsClicked = false;
        return false;
      }
      $('a.fieldset-title').css('visibility', 'hidden');
    });

     if ($('a.search-term').length) {
      $('a.extend-search').attr('id','search-extend-term');
    }
  });

  function attachFoldOut() {
    var foldout = Drupal.settings.ting_extended_search["ting_extended_search_foldout_event"];
    if (foldout) {
      $('.search .collapsible .fieldset-legend > a, .search .form-actions > a.fieldset-title').on('mouseenter', function() {
        $('.search .form-actions > a.fieldset-title').click();
      })

      $('#edit-advanced').on('mouseleave', function() {
        $('.search .form-actions > a.fieldset-title').click();
      })
    }
  }

})(jQuery);
