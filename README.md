# winpatcher_x86
A library of tools for placing patches and hooks into target x86 program code.

You should call exported GetPatcherX86 function from your code to get IPatcher instance. The IPatcher interface provides most of the functionlity of the winpatcher_x86 library.

It is used in the MMDoC Revival project: https://sites.google.com/site/mmdoc4ever

Some code example from it:

```c++
//Fix banish invisible card original bug

_P->SetLoHook(addr(0x5B1450), [](LoHookContext* c) -> int
  {
    if (c->eax && c->ecx)
      return EXEC_DEFAULT;
    c->return_address = addr(0x5B1457);
    return SKIP_DEFAULT;
  });
  
HIHOOK(addr(0x54AA10), SPLICE_, EXTENDED_,
  int, __thiscall, sub_54AA10, (_ptr_ this_, int a2),
  {
    if (!this_)
    {
      //ConsoleOut("\n %X: sub_54AA10", RetAddr());
      return 1;
    }
    return DefaultFunc(this_, a2);
  }
);
```

