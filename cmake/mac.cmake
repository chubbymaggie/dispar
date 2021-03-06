set(SDK_MIN 10.8)

# Try to pick the newest!
set(SDKS 10.12 10.11 10.10 10.9 10.8)

foreach (sdk ${SDKS})
  set(DEV_SDK "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX${sdk}.sdk")
  if (EXISTS "${DEV_SDK}" AND IS_DIRECTORY "${DEV_SDK}")
    set(found_sdk YES)
    break()
  endif()

  set(DEV_SDK "/Developer/SDKs/MacOSX${sdk}.sdk")
  if (EXISTS "${DEV_SDK}" AND IS_DIRECTORY "${DEV_SDK}")
    set(found_sdk YES)
    break()
  endif()
endforeach()

if (NOT found_sdk)
  message(FATAL_ERROR "Could not find Mac OS X SDK version 10.8 - 10.12!")
endif()

add_definitions(
  -DMAC
  -DGCC_VISIBILITY
  -mmacosx-version-min=${SDK_MIN}
  )

set(CMAKE_OSX_SYSROOT ${DEV_SDK})

# Silence annoying "ranlib: file: ...o has no symbols" warnings! On Mac the ar utility will run
# ranlib, which causes the warning. Using the "Src" argument stops ar from executing ranlib, and
# when ranlib is executed normally we give it "-no_warning_for_no_symbols" to suppress the warning.
set(CMAKE_C_ARCHIVE_CREATE "<CMAKE_AR> Scr <TARGET> <LINK_FLAGS> <OBJECTS>")
set(CMAKE_CXX_ARCHIVE_CREATE "<CMAKE_AR> Scr <TARGET> <LINK_FLAGS> <OBJECTS>")
set(CMAKE_C_ARCHIVE_FINISH "<CMAKE_RANLIB> -no_warning_for_no_symbols -c <TARGET>")
set(CMAKE_CXX_ARCHIVE_FINISH "<CMAKE_RANLIB> -no_warning_for_no_symbols -c <TARGET>")
