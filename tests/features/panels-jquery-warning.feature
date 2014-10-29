Feature: Warn admins about incompatible jQuery

  @drush
  Scenario: Admin is warned if using incompatible version of jQuery with Panels
    Given the module "jquery_update" is enabled
      And the module "panels" is enabled
      And the version of jQuery used is "1.10"
      And I am on "/user"
      And I fill in "admin" for "edit-name"
      And I fill in "admin" for "edit-pass"
      And I press "Log in"
      And I am on "/admin/reports/status"
    Then I should see the text "there are known issues using jQuery"
