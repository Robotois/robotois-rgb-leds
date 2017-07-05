#ifndef RGBWRAPPER_H
#define RGBWRAPPER_H

#include <node.h>
#include <node_object_wrap.h>
#include "../RGBModule.h"

class RGBWrapper : public node::ObjectWrap {
public:
  static void Init();
  static void NewInstance(const v8::FunctionCallbackInfo<v8::Value>& args);

private:
  explicit RGBWrapper(uint8_t _add = 0x00);
  ~RGBWrapper();

  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);

  static void allOn(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void allOff(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void allBlink(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void turnOn(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void turnOff(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void blink(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void rainbow(const v8::FunctionCallbackInfo<v8::Value>& args);

  static void release(const v8::FunctionCallbackInfo<v8::Value>& args);

  static v8::Persistent<v8::Function> constructor;

  RGBModule *rgb;
};

#endif
