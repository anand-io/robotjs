#include <node.h>
#include <nan.h>
#include <v8.h>
#include <vector>
#include "mouse.h"
#include "deadbeef_rand.h"
#include "keypress.h"
#include <unistd.h>
using namespace v8;

/*
 __  __                      
|  \/  | ___  _   _ ___  ___ 
| |\/| |/ _ \| | | / __|/ _ \
| |  | | (_) | |_| \__ \  __/
|_|  |_|\___/ \__,_|___/\___|

 */

NAN_METHOD(moveMouse) 
{
  NanScope();
  if (args.Length() < 2) 
  {
    // ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
    // return scope.Close(Undefined());
  }
  size_t x = args[0]->Int32Value();
  size_t y = args[1]->Int32Value();

  MMPoint point;
  point = MMPointMake(x, y);
  moveMouse(point);
  NanReturnValue(NanNew("1"));
}

NAN_METHOD(getMousePos) 
{
  NanScope();

  MMPoint pos = getMousePos();

  //Return object with .x and .y.
  Local<Object> obj = NanNew<Object>();
  obj->Set(NanNew<String>("x"), NanNew<Number>(pos.x));
  obj->Set(NanNew<String>("y"), NanNew<Number>(pos.y));
  NanReturnValue(obj);
}

NAN_METHOD(mouseClick) 
{
  NanScope();

   MMMouseButton button;

  char *type=*v8::String::Utf8Value(args[0]->ToString());

   if(strcmp(type,"left"))
   {
     button=LEFT_BUTTON;
   }
   else
   {
     if(strcmp(type,"right"))
     {
      button=RIGHT_BUTTON;
     }
     else
     {
      button=LEFT_BUTTON;
     }
   }

  clickMouse(button);

  NanReturnValue(NanNew("1"));
}

// NAN_METHOD(drag)
// {
//   NanScope();
//   MMPoint pos=getMousePos();
//   NanReturnValue(NanNew<Number>(pos.x));
// }

NAN_METHOD(scroll)
{
  NanScope();
  scroll();
  NanReturnValue(NanNew("1"));
}
/*
 _  __          _                         _ 
| |/ /___ _   _| |__   ___   __ _ _ __ __| |
| ' // _ \ | | | '_ \ / _ \ / _` | '__/ _` |
| . \  __/ |_| | |_) | (_) | (_| | | | (_| |
|_|\_\___|\__, |_.__/ \___/ \__,_|_|  \__,_|
          |___/           
 */

// char *get(v8::Local<v8::Value> value, const char *fallback = "") 
// {
//     if (value->IsString()) 
//     {
//         v8::String::AsciiValue string(value);
//         char *str = (char *) malloc(string.length() + 1);
//         strcpy(str, *string);
//         return str;
//     }
//     char *str = (char *) malloc(strlen(fallback) + 1);
//     strcpy(str, fallback);
//     return str;
// }

NAN_METHOD (keyTap) 
{
  NanScope();

  MMKeyFlags flags = MOD_NONE;
  
  const char c = (*v8::String::Utf8Value(args[0]->ToString()))[0];

  tapKey(c, flags);

  NanReturnValue(NanNew("1"));
}

//print the list of charecters
NAN_METHOD(typeString)
{
   NanScope();
   MMKeyFlags flags= MOD_NONE;

   char *c=*v8::String::Utf8Value(args[0]->ToString());
   size_t i=0;

   for(i=0;i<strlen(c);i++)
   {
     tapKey(c[i],flags);
     usleep(2000);
   }
}

// Handle<Value> typeString(const Arguments& args) 
// {
//   HandleScope scope;

//   char *str = get(args[0]);

//   typeString(str);

//   return scope.Close(String::New("1"));
// }

void init(Handle<Object> target) 
{

  target->Set(NanNew<String>("moveMouse"),
    NanNew<FunctionTemplate>(moveMouse)->GetFunction());

  target->Set(NanNew<String>("getMousePos"),
    NanNew<FunctionTemplate>(getMousePos)->GetFunction());

  target->Set(NanNew<String>("mouseClick"),
    NanNew<FunctionTemplate>(mouseClick)->GetFunction());

  target->Set(NanNew<String>("keyTap"),
    NanNew<FunctionTemplate>(keyTap)->GetFunction());

  target->Set(NanNew<String>("typeString"),NanNew<FunctionTemplate>(typeString)->GetFunction());

  target->Set(NanNew<String>("scroll"),NanNew<FunctionTemplate>(scroll)->GetFunction());

  // target->Set(NanNew<String>("typeString"),
  //   NanNew<FunctionTemplate>(typeString)->GetFunction());

}

NODE_MODULE(robotjs, init)
