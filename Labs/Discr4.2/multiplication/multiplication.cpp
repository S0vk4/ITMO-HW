#include <iostream>

using namespace std;

int main()
{
    freopen("multiplication.out", "w", stdout);
    cout << "start: s\naccept: ac\nreject: rj\nblank: =\ns 0 -> s 0 <\ns 1 -> s 1 <\ns = -> sz + <\nsz = -> r 0 >\nr + -> r + >\nr * -> r * >\nr 0 -> r 0 >\nr 1 -> r 1 >\nr 2 -> r 2 >\nr 3 -> r 3 >\nr = -> c = <\n\nc 0 -> sh = <\nc 1 -> add = <\nc * -> end = <\n\nsh 0 -> sh 0 <\nsh 1 -> sh 1 <\nsh * -> sh * <\nsh + -> h + <\nh 2 -> h 2 <\nh 3 -> h 3 <\nh 0 -> r 2 >\nh 1 -> r 3 >\nh = -> r 2 >\n\nadd 0 -> add 0 <\nadd 1 -> add 1 <\nadd * -> pb * <\n\npr 0 -> pr 0 >\npr 1 -> pr 1 >\npr 2 -> pr 2 >\npr 3 -> pr 3 >\npr 4 -> pr 4 >\npr 5 -> pr 5 >\npr + -> pr + >\npr 6 -> pb 6 <\npr 7 -> pb 7 <\n\npb 0 -> pbz 6 <\npb 1 -> pbnz 7 <\npb + -> pend + <\n\npbz 1 -> pbz 1 <\npbz 0 -> pbz 0 <\npbz + -> paz + <\n\npaz 2 -> paz 2 <\npaz 3 -> paz 3 <\npaz 4 -> paz 4 <\npaz 5 -> paz 5 <\npaz 0 -> pr 4 >\npaz 1 -> pr 5 >\npaz = -> pr 4 >\n\npbnz 1 -> pbnz 1 <\npbnz 0 -> pbnz 0 <\npbnz + -> panz + <\n\npanz 2 -> panz 2 <\npanz 3 -> panz 3 <\npanz 4 -> panz 4 <\npanz 5 -> panz 5 <\npanz 0 -> pr 5 >\npanz 1 -> pcanz 4 <\npanz = -> pr 5 >\n\npcanz 0 -> pr 1 >\npcanz 1 -> pcanz 0 <\npcanz = -> pr 1 >\n\npend 3 -> pend 3 <\npend 2 -> pend 2 <\npend 4 -> pclr 2 <\npend 5 -> pclr 3 <\npend 1 -> pclr 3 <\npend 0 -> pclr 2 <\npend = -> pclr 2 <\n\npclr 4 -> pclr 0 <\npclr 5 -> pclr 1 <\npclr 1 -> pl 1 >\npclr 0 -> pl 0 >\npclr = -> pl = >\n\npl 0 -> pl 0 >\npl 1 -> pl 1 >\npl 2 -> pl 2 >\npl 3 -> pl 3 >\npl + -> pl + >\npl 6 -> pl 0 >\npl 7 -> pl 1 >\npl * -> r * >\n\nend 0 -> end = <\nend 1 -> end = <\nend + -> endclr = <\nendclr 2 -> endclr 0 <\nendclr 3 -> endclr 1 <\nendclr 0 -> endclr 0 <\nendclr 1 -> endclr 1 <\nendclr = -> clrz = >\n\nclrz 0 -> clrz = >\nclrz 1 -> ac 1 ^\nclrz = -> ac 0 ^\n" << flush;
    return 0;
}
