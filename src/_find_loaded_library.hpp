// Cribbed from: drake @ 4c6246197, `find_loaded_library.cpp`

#include <cassert>

#include <libgen.h>  // dirname
#include <string.h>
#include <unistd.h>

#include <link.h>
#include <linux/limits.h>  // PATH_MAX

namespace rcpputils {
namespace {

// Gets the list of all the shared objects that have been loaded. Finds
// `library_file` in the list, and returns its absolute directory path.
// This function is specific to Linux.
std::string LoadedLibraryPath(const std::string& library_file) {
  using std::string;
  void* handle = dlopen(NULL, RTLD_NOW);
  link_map *map;
  dlinfo(handle, RTLD_DI_LINKMAP, &map);
  // Loop over loaded shared objects until `library_file` is found.
  while (map) {
    // Avoid using `basename()` and `dirname()` implemented in `libgen.h`
    // because as stated in `libgen.h` documentation [1], both functions
    // may modify the content of the input c-string (which happened in the
    // original implementation and resulted in a bug).
    // [1] http://man7.org/linux/man-pages/man3/basename.3.html#DESCRIPTION
    const char* pos_slash = strrchr(map->l_name, '/');
    if (pos_slash && !strcmp(pos_slash + 1, library_file.c_str())) {
      // Check if path is relative. If so, make it absolute.
      if (map->l_name[0] != '/') {
        char buf[PATH_MAX];
        ssize_t readlink_res = readlink("/proc/self/exe", buf, sizeof(buf));
        assert(readlink_res >= 0 && readlink_res < PATH_MAX);
        buf[readlink_res] = '\0';
        return string(dirname(buf)) + "/" +
              string(map->l_name, pos_slash - map->l_name);
      } else {
        return string(map->l_name, pos_slash - map->l_name);
      }
    }
    map = map->l_next;
  }
  return "";
}

}  // namespace
}  // namespace rcpputils
