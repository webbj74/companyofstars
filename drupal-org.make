api = 2
core = 7.x

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Contributed modules.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Address Field: Provides Address Field Widget
projects[addressfield][type] = "module"
projects[addressfield][subdir] = "contrib"
projects[addressfield][version] = "1.1"

; CAPTCHA: Spam deterrent
projects[captcha][type] = "module"
projects[captcha][subdir] = "contrib"
projects[captcha][version] = "1.2"

; CTools: Misc Drupal Magic
projects[ctools][type] = "module"
projects[ctools][subdir] = "contrib"
projects[ctools][version] = "1.7"

; Date: Provides Date Field Widget
projects[date][type] = "module"
projects[date][subdir] = "contrib"
projects[date][version] = "2.8"

; Entity API: Required by Field Collection
projects[entity][type] = "module"
projects[entity][subdir] = "contrib"
projects[entity][version] = "1.6"

; Features: Encapsulates Drupal Configuration
;   Used to encapsulate the Chartered Body content type
projects[features][type] = "module"
projects[features][subdir] = "contrib"
projects[features][version] = "2.5"

; Field Collection: Allows a content type to have multiple sets of fields.
;  Used to track historic changes within the Chartered Body content type
projects[field_collection][type] = "module"
projects[field_collection][subdir] = "contrib"
projects[field_collection][version] = "1.0-beta8"

; jQuery Update: Used by Zurb Foundation theme
projects[jquery_update][version] = "2.5"
projects[jquery_update][type] = "module"
projects[jquery_update][subdir] = "contrib"

; Libraries: Required by Zurb Foundation theme
projects[libraries][version] = "2.2"
projects[libraries][type] = "module"
projects[libraries][subdir] = "contrib"

; Migrate: Used to import from data set
projects[migrate][type] = "module"
projects[migrate][subdir] = "contrib"
projects[migrate][version] = "2.7"

; Navbar: Nice Admin UI
projects[navbar][version] = "1.5"
projects[navbar][type] = "module"
projects[navbar][subdir] = "contrib"

; ReCAPTCHA: Spam deterrent
projects[recaptcha][type] = "module"
projects[recaptcha][subdir] = "contrib"
projects[recaptcha][version] = "1.11"


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Themes
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

projects[ember][version] = "2.x-dev"
projects[ember][type] = "theme"
projects[ember][subdir] = "contrib"
projects[ember][download][type] = "git"
projects[ember][download][branch] = "7.x-2.x"

projects[zurb-foundation][version] = "5.x-dev"
projects[zurb-foundation][type] = "theme"
projects[zurb-foundation][subdir] = "contrib"
projects[zurb-foundation][download][type] = "git"
projects[zurb-foundation][download][revision] = "d4c28f1"
projects[zurb-foundation][download][branch] = "7.x-5.x"


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Libraries
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

libraries[backbone][download][type] = "get"
libraries[backbone][download][url] = "https://github.com/jashkenas/backbone/archive/1.1.0.zip"

libraries[modernizr][download][type] = "get"
libraries[modernizr][download][url] = "https://github.com/Modernizr/Modernizr/archive/v2.7.1.zip"

libraries[underscore][download][type] = "get"
libraries[underscore][download][url] = "https://github.com/jashkenas/underscore/archive/1.5.2.zip"

