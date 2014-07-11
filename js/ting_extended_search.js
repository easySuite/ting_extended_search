/**
 * @file JavaScript for extended search form
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
})(jQuery);

