#include "./MonoInterface.h"
#include "./MonoTKHeader.h"
#include<QDebug>

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>

MonoInterface::MonoInterface(){
  //https://www.mono-project.com/docs/advanced/embedding/
  domain      = mono_jit_init ("MonoTK"); //Namespace of the assembly
  assembly = mono_domain_assembly_open (domain, "test.exe");

  if (!assembly)
  {
    qInfo("Assembly was not created or not found.");
    return;
  }
  else
  {
    qInfo("Assembly loaded successfully.");
  }
}
MonoInterface::~MonoInterface(){
  //Note that for current versions of Mono, the mono runtime can’t be reloaded into the same process,
  //so call mono_jit_cleanup() only if you’re never going to initialize it again.
  mono_jit_cleanup (domain);
}
void MonoInterface::runCSharpApp() {
  //std::string app_location = "C:\\git\\MonoTK\\bin\\test.exe";

  //int argc = 1;
  //char** argv = new char*[1];
  //argv[1] = new char[256];
  //memset(argv[1], 0, 256);
  //memcpy(argv[1], app_location.c_str(), app_location.length());

  //Instead of copying /lib to the root folder this should be called.
  //mono_set_dirs("..\\external\\Mono\\lib", "..\\external\\Mono\\etc");

  //mono_config_parse (NULL);

  int retval = mono_jit_exec(domain, assembly, Globals::argc, Globals::argv);
}
