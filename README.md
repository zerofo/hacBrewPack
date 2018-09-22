# hacBrewPack

[![License: GPL v2](https://img.shields.io/badge/License-GPL%20v2-blue.svg)](https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html)

hacBrewPack is a tool for creating Nintendo Switch NCAs (Nintendo Content Archive) from homebrews and pack them into NSPs (Nintendo Submission Package)  
hacBrewPack is WIP and it's at very early stages  
  
Thanks: SciresM, yellows8, Adubbz, SwitchBrew

## Usage

### Keys
You should place your keyset file with "keys.dat" filename in the same folder as hacBewPack  
Alternatively, You can use -k or --keyset option to load your keyset file  
Required keys are:  

Key Name | Description
-------- | -----------
header_key | NCA Header Key
key_area_key_application_xx | Application key area encryption keys

### Compiling Homebrew
You need to compile homebrew with proper makefile, you can use the one in template folder  
You must use valid lower-case TitleID in Makefile and npdm.json. Valid TitleID range is: 0x0100000000000000 - 0x01ffffffffffffff  
Both TitleIDs in Makefile and npdm.json must be the same  
Compiled homebrew must have following files:  
```
build\exefs\main  
build\exefs\main.npdm  
[TARGET].nacp  
```
You must place created 'main' and 'main.npdm' files in exefs folder, you can find them in build/exefs  
You must rename created nacp file to 'control.nacp' and place it in control folder  

### Icon
You should place your icon with "icon_{Language}.dat" file name in control folder, "icon_AmericanEnglish.dat" is the default one if you don't manually edit your nacp. dat files are just renamed jpg files  
Check [switchbrew](http://switchbrew.org/index.php/Settings_services#LanguageCode) for more info about language names  
Your icon file format must be JPEG with 256x256 dimensions  
It's highly recomended to delete unnecessary exif data from your jpeg file (easy way: Open icon with GIMP or Paint, save as bmp, Open it again and save as jpeg)  
If you see placeholder instead of icon after installing nsp, It's likely due to exif data  
If you have some exif data that horizon os doesn't like (like Camera Brand), Your app may leave in installing state in qlaunch  
If you don't put your icon in control folder, you'll see a general icon after installing nsp (i don't recommend this)  
### Logo
"logo" folder should contain "NintendoLogo.png" and "StartupMovie.gif", they'll appear when the app is loading  
Both files are not licensed according to [switchbrew](http://switchbrew.org/index.php/NCA_Content_FS) but i didn't include them anyway, You can also replace these files with custom ones  
You can use --nologo if you don't have any custom logo and you don't have the original ones, as the result switch will show a black screen without nintendo logo at top left and switch animation on bottom right  
### CLI Options:  
```
*nix: ./hacbrewpack [options...]  
Windows: .\hacbrewpack.exe [options...]  
  
Options:  
-k, --keyset             Set keyset filepath, default filepath is ./keys.dat  
-h, --help               Display usage  
--tempdir                Set temp directory filepath, default filepath is ./hacbrewpack_temp/  
--ncadir                 Set output nca directory path, default path is ./hacbrewpack_nca/  
--nspdir                 Set output nsp directory path, default path is ./hacbrewpack_nsp/  
--exefsdir               Set program exefs directory path, default path is ./exefs/  
--romfsdir               Set program romfs directory path, default path is ./romfs/  
--logodir                Set program logo directory path, default path is ./logo/  
--controldir             Set control romfs directory path, default path is ./control/  
--keygeneration          Set keygeneration for encrypting key area keys  
--noromfs                Skip creating program romfs section  
--nologo                 Skip creating program logo section  
--plaintext              Skip encrypting sections and set section header block crypto type to plaintext  
```
Also check template folder for default folder structure, makefile, npdm json and other useful info  
  
**Delete nca(hacbrewpack_nca) and temp(hacbrewpack_temp) folders before start or you may have bad nsp**

## Licensing

This software is licensed under the terms of the GNU General Public License, version 2.  
You can find a copy of the license in the LICENSE file.  
Portions of project HacBrewPack are parts of other projects, make sure to check LICENSES folder