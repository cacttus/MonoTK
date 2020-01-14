#pragma once

#ifndef MONOINTERFACE_H
#define MONOINTERFACE_H

typedef struct _MonoAssembly MonoAssembly;
typedef struct _MonoDomain MonoDomain;

class MonoInterface{
public:
  MonoInterface();
  virtual ~MonoInterface();
  void runCSharpApp();

  MonoDomain* domain;
  MonoAssembly* assembly;
};

#endif // MONOINTERFACE_H
