Hi,

It is a document that describes a preparing of build environment. So, lets do this.

1 Get another chroot
---------------------
As you know to compile some specific programs, you need to provide specific libraries. I am not an expert, so I prefer to don't interpose in my work system. But how to do this? I recommend using the second chroot in which you can do all things without painful consequences.
The easiest way is to use script prepared by chromium team.
    * article: https://code.google.com/p/chromium/wiki/UsingALinuxChroot
    * script: https://code.google.com/p/chromium/codesearch#chromium/src/build/install-chroot.sh
To create chroot I choosed Ubuntu Precise x64.

2 Install libraries
--------------------
To compile sources you need to install some libraries.
Till now there are:
    * SQLite3
    * boost
Maybe in future:
    * SOCI
    * yb-orm
I attach scripts to installing these libraries in the last avaliable versions (according to November 16, 2013).

3 There is no third step.
--------------------------

I presented you my way, only don't expect there are no other solutions. Of course it could be done in many other ways. 

Good lock :)
