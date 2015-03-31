from AutotoolsBuilder import AutotoolsBuilder
import os

class LibMongoClientBuilder(AutotoolsBuilder):

    def environment_override(self):
        self._add_extra_env(
         {"PKG_CONFIG_PATH" : "%s/lib/pkgconfig"%(self.install_dir),
          "PATH": os.environ['PATH'] + ":%s/bin"%(self.install_dir),
         })



def get_builder():
    return LibMongoClientBuilder(get_default_config_opts())

def get_default_config_opts():
    try:
        import configure_opts
    except ImportError:
        return None
    else:
        return configure_opts.default_opts

