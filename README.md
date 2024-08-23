# Crzgames - Libraries C/C++ - Linux

## Informations sur les types de fichier des bibliothèques C/C++ par rapport au system ou/et du compiler Linux :
Compiler : GCC <br />

Bibliothèque dynamique/partagée : .so<br />
Bibliothèque statique : .a<br />

<br /><br /><br /><br />


## Supported architecture for Linux system :
- Linux x86_64 <br />

<br /><br /><br /><br />


## Documentation des dépendances pour chacune des librairies :
hiredis :
  1. dossier include (hiredis) -> à linker
  2. libhiredis.a -> librairie static à linker <br /><br />

jwt-cpp :
1. dossier include (jwt-cpp, openssl, picojson) -> à linker
2. libssl, libcrypto -> à linker  <br /><br />
   
RCENet : 
  1. dossier include (rcenet) -> à linker
  2. librcenet.a -> librairies static à linker <br /><br />

Nats Client C :
  1. dossier include (nats, protobuf-c) -> à linker
  2. libnats_static.a, libprotobuf-c.a -> à linker

SDL2 : 
  1. dossier include (SDL) -> à linker
  2. libSDL2.a, libSDL2main.a -> librairies static à linker
  3. libSDL2.dylib -> dossier bin <br /><br />

SDL2_image : 
  1. dossier include (SDL2_image) -> à linker
  2. libSDL2_image.a -> à linker
  3. libSDL2_image.dylib -> dossier bin <br /><br />

SDL2_ttf : 
  1. dossier include (SDL2_ttf) -> à linker
  2. libSDL2_ttf.a -> à linker
  3. libSDL2_ttf.dylib -> dossier bin <br /><br />

SDL2_mixer : 
  1. dossier include (SDL2_mixer) -> à linker
  2. libSDL2_mixer.a -> à linker
  3. libSDL2_mixer.dylib -> dossier bin <br /><br />
  
OpenSSL : 
  1. dossier include (openssl/crypto/internal) -> à linker
  2. libssl.a, libcrypto.a (libssl.a à linker avant libcrypto.a) -> à linker

<br /><br /><br /><br />


## Documentation pour construire les librairies, permet de récupérer les .h / .a / .so des librairies (pour mettre à jour les librairies si il faut) :
### Setup Environment :
1. Install packages apt (à faire depuis root) :
```bash
  sudo apt update &&
  sudo apt upgrade &&
  sudo apt-get install -y git g++ make libtool automake autopoint pkg-config flex bison lua5.2 &&
  sudo apt-get install -y curl &&
  sudo apt-get install -y openssl &&
  sudo apt-get install -y libssl-dev &&
```

2. Set sudo rights for user (a faire depuis root, remplacer 'user' par le nom de l'utilisateur du système linux par exemple : debian) :
```bash
  sudo usermod -aG sudo user
```

3. Install homebrew (à faire depuis user) :
```bash
  /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

4. Après l'installation de homebrew il faut importer les variables d'environnement et installer les deux librairies (à faire depuis user, modifier 'debian' par le nom d'utilisateur si besoin) :
```bash
  echo '# Set PATH, MANPATH, etc., for Homebrew.' >> /home/debian/.bashrc && 
  echo 'eval "$(/home/linuxbrew/.linuxbrew/bin/brew shellenv)"' >> /home/debian/.bashrc && 
  eval "$(/home/linuxbrew/.linuxbrew/bin/brew shellenv)" &&
  sudo apt-get install -y build-essential &&
  brew install gcc
```

<br /><br />


### Librairies à récupérer :
#### Informations TRES IMPORTANT - Libraries / Executable :
1. Connaître l'architecture ciblée (x86_64, i686, etc.) d'un fichier exécutable ou d'une library shared (.so) :
```bash
file path/vers/libmylib.so # lib shared .so
file path/vers/mygame-test # executable

# Exemple :
# ubuntu@ns3101892:~/Crzgames_GameEngine/dest-exe$ file libSDL2-2.0.so.0.2800.5
# libSDL2-2.0.so.0.2800.5: ELF 64-bit LSB shared object, x86-64, version 1 (SYSV), dynamically linked, BuildID[sha1]=b4f67b323bb04da6d8dc1b90f5b03f8357e7f126, not stripped
```
2. Pour checker les sous dépendences d'une library shared (.so) ou les dépendences de l'executable :
```bash
# Qui permet de voir les sous dépendences de libmylib.so ou de l'executable
ldd path/vers/libmylib.so # lib shared .so
ldd path/vers/myexecutable # executable

# Exemple :
# ubuntu@ns3101892:~/Crzgames_GameEngine/dest-exe$ ldd mygame-test
        # linux-vdso.so.1 (0x00007ffed4dfe000)
        # libfmod.so.13 => /home/ubuntu/Crzgames_GameEngine/dest-exe/./libfmod.so.13 (0x00007f4ecacff000)
        # libenet.so.7 => /home/ubuntu/Crzgames_GameEngine/dest-exe/./libenet.so.7 (0x00007f4ecaa00000)
        # libSDL2-2.0.so.0 => /home/ubuntu/Crzgames_GameEngine/dest-exe/./libSDL2-2.0.so.0 (0x00007f4eca864000)
```
3. Lorsque vous compilez un exécutable sur un système hôte (le système sur lequel vous effectuez la compilation), l'exécutable se base sur les versions des bibliothèques disponibles sur ce système, y compris la glibc (GNU C Library) <br />
```bash
# Get version GLIBC : ldd --version

# Check les dépendences d'un executable et le minimum qu'il faut pour les lib pour GLIBC
objdump -T myapp | grep GLIBC

# Donc la on vas regarder il faut au minimum quel version GLIBC au minimum pour pouvoir construire l'executable avec toute les libraries
# Exemple :
# ubuntu@ns3101892:~/Crzgames_GameEngine/dest-exe$ objdump -T mygame-test | grep GLIBC
# 0000000000000000      DF *UND*  0000000000000000 (GLIBC_2.2.5) printf
# 0000000000000000      DF *UND*  0000000000000000 (GLIBCXX_3.4.21) _ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE6appendEPKcm
# 0000000000000000      DF *UND*  0000000000000000 (GLIBCXX_3.4) _ZNSaIcED2Ev
# 0000000000000000      DF *UND*  0000000000000000 (GLIBCXX_3.4.21) _ZSt7getlineIcSt11char_traitsIcESaIcEERSt13basic_istreamIT_T0_ES7_RNSt7__cxx1112basic_stringIS4_S5_T1_EE
# 0000000000000000      DF *UND*  0000000000000000 (GLIBCXX_3.4) _ZNSt14basic_ifstreamIcSt11char_traitsIcEE5closeEv
# 0000000000000000      DF *UND*  0000000000000000 (GLIBCXX_3.4) _ZNSt14basic_ifstreamIcSt11char_traitsIcEED1Ev
# 0000000000000000      DF *UND*  0000000000000000 (GLIBCXX_3.4.21) _ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE7compareEPKc
# 0000000000000000      DF *UND*  0000000000000000 (GLIBCXX_3.4.21) _ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE7replaceEmmRKS4_
# 0000000000000000      DF *UND*  0000000000000000 (GLIBCXX_3.4.21) _ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE13get_allocatorEv
# 0000000000000000      DF *UND*  0000000000000000 (GLIBCXX_3.4.21) _ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE5c_strEv
```
4. Pour modifier les chemin des sous dépendences d'une librairie partagé (.so) ou les dépendences d'un executabe via RPATH (Runtime Library Search Path) :
```bash
# Install package for RPATH
sudo apt-get update
sudo apt-get install patchelf

# Nous avons par exemple 'libSDL2.so' avec des sous dépendences éparpiller sur le système, pour savoir faire la commande :
ldd libSDL2.so
# Exemple :
# debian@vps-4e8a304b:~/Crzgames_GameEngine/test$ ldd libSDL2_image.so
        # linux-vdso.so.1 (0x00007fff1cd4a000)
        # libpng16.so.16 => /home/linuxbrew/.linuxbrew/opt/libpng/lib/libpng16.so.16 (0x00007f9f4409d000)
        # libjxl.so.0.9 => /home/linuxbrew/.linuxbrew/opt/jpeg-xl/lib/libjxl.so.0.9 (0x00007f9f43c00000)
        # libjpeg.so.8 => /home/linuxbrew/.linuxbrew/opt/jpeg-turbo/lib/libjpeg.so.8 (0x00007f9f43fe0000)
        # libtiff.so.6 => /home/linuxbrew/.linuxbrew/opt/libtiff/lib/libtiff.so.6 (0x00007f9f43f50000)
        # libavif.so.16 => /home/linuxbrew/.linuxbrew/opt/libavif/lib/libavif.so.16 (0x00007f9f43f28000)
        # ...

# On vas récupérer toute ces sous dépendences les mettre dans le même dossier que la lib 'libSDL2.so'
# Ce qui vas permettre lorsqu'ont vas bundle l'application pour en faire un .AppImage que chaque library shared recherche ces sous dépendences dans le dossier lui-même
patchelf --set-rpath '$ORIGIN' /chemin/vers/libSDL2.so

# Si le chemin ne veut pas être modifier c'est qu'il y a un path RUNPATH
# Utilisé l'option --force-rpath avec patchelf pour s'assurer que le RPATH est utilisé même en présence d'un RUNPATH :
patchelf --set-rpath '$ORIGIN' --force-rpath /chemin/vers/libSDL2.so 
```
<br /><br />

#### Informations - Divers : 
1. Quand on installe des librairies via brew les librairies sont installer depuis : /home/linuxbrew/.linuxbrew/Cellar/
2. Informations .AppImage : <br />
   Garder à l'esprit quand on crée une .AppImage (avec des lib par exemple pour : x86_64), elle sera compatible sur la totalité des distribution Linux mais seulement pour x86_64.
   
<br /><br /><br />

jwt-cpp : 
1. Il faudra récupérer la dernière version release : https://github.com/Thalhammer/jwt-cpp/releases (source.zip)
2. Récupérer le dossier 'jwt-cpp' et 'picojson' dans le dossier include du dossier précédemment télécharger.
   
<br /><br />

hiredis : 
1. Il faudra récupérer la dernière version release : https://github.com/redis/hiredis/releases
2. Construire la lib :
```bash
cd hirelis
mkdir build
cmake .. -DBUILD_SHARED_LIBS=OFF
make
```
3. Récupérer la lib 'libhiredis.a' et fichier include
   
<br /><br />

OpenSSL : 
1. Il faudra cloner le github de OpenSSL officiel à partir d'une branche spécifique pour cibler la version comme ceci :
```bash
# Changer la version de la branche de OpenSSL si besoin
git clone -b openssl-3.3.1 https://github.com/openssl/openssl.git
cd openssl/
```
2. Construire OpenSSL pour Linux x86_64 :
```bash
mkdir build-x86_64 && cd build-x86_64
../Configure linux-x86_64 -static --static --prefix=$PWD
make
sudo make install
```

<br /><br />

SDL2 :
1. Récupérer la dernière version latest (.tar.gz) : https://github.com/libsdl-org/SDL/releases
2. Faire un 'cd' a la racine du dossier télécharger.
3. Créer un dossier :
  ```bash
  mkdir build-sdl && cd build-sdl
  ```
4. Configurer et construire la lib
  ```bash
  ../configure --prefix=$PWD --enable-static=yes --enable-shared=no
  make
  sudo make install
  ```
6. Récupérer la librairie static (.a) et dossier include dans le dossier ci-dessus (lib et include)
   
<br /><br />

SDL2_image :
1. Récupérer la dernière version latest (.tar.gz) : https://github.com/libsdl-org/SDL_image/releases
2. Faire un 'cd' a la racine du dossier télécharger.
3. Installer les dépendences pour construire la librairie :
  ```bash
  sudo apt update
  sudo apt install libsdl2-dev libpng-dev libjpeg-dev libtiff-dev libwebp-dev
  ```
4. Créer un dossier :
  ```bash
  mkdir build-sdlimage && cd build-sdlimage
  ```
5. Configurer et construire la lib
  ```bash
  ../configure --prefix=$PWD --enable-static=yes --enable-shared=no
  make
  sudo make install
  ```
6. Récupérer la librairie static (.a) et dossier include dans le dossier ci-dessus (lib et include)
   
<br /><br />

SDL2_ttf :
1. Récupérer la dernière version latest (.tar.gz) : https://github.com/libsdl-org/SDL_ttf/releases
2. Faire un 'cd' a la racine du dossier télécharger.
3. Installer les dépendences pour construire la librairie :
  ```bash
  sudo apt update
  sudo apt install libsdl2-dev libfreetype6-dev
  ```
4. Créer un dossier :
  ```bash
  mkdir build-sdlttf && cd build-sdlttf
  ```
5. Configurer et construire la lib
  ```bash
  ../configure --prefix=$PWD --enable-static=yes --enable-shared=no
  make
  sudo make install
  ```
6. Récupérer la librairie static (.a) et dossier include dans le dossier ci-dessus (lib et include)
   
<br /><br />

SDL2_mixer :
1. Récupérer la dernière version latest (.tar.gz) : https://github.com/libsdl-org/SDL_mixer/releases
2. Installer les dépendences pour construire la librairie :
  ```bash
  sudo apt update
  sudo apt install libsdl2-dev
  sudo apt install libogg-dev libvorbis-dev libflac-dev libmodplug-dev libmpg123-dev
  ```
3. Faire un 'cd' a la racine du dossier télécharger.
4. Créer un dossier :
  ```bash
  mkdir build-sdlmixer && cd build-sdlmixer
  ```
5. Configurer et construire la lib
  ```bash
  ../configure --prefix=$PWD --enable-static=yes --enable-shared=no
  make
  sudo make install
  ```
6. Récupérer la librairie static (.a) et dossier include dans le dossier ci-dessus (lib et include)
   
<br /><br />

Nats Client C :
1. Run a command install packages for protobuf-c to Nats :
    ```bash
    sudo apt-get install -y libprotobuf-dev libprotoc-dev protobuf-compiler libssl-dev libprotobuf-c-dev
    ```
2. Télécharger la dernière version du repository : https://github.com/nats-io/nats.c/releases (.tar.gz)
3. Go in repository, and run command :
  ```bash
  # Generate lib
  mkdir build && cd build && cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$(pwd)/build-nats && sudo make install
  ``` 
4. Récupérer la librairie depuis le repo : ./build-nats/lib/ (libnats_static.a) <br />
   Récupérer le dossier include (.h) depuis le repo : ./build-nats/include/ <br /><br />

protobuf-c :
1. Run a command install packages :
    ```bash
    sudo apt-get install autoconf automake libtool make protobuf-compiler libprotobuf-dev pkg-config
    ```
2. Télécharger la dernière version du repository : https://github.com/protobuf-c/protobuf-c/releases (.tar.gz)
3. Go in repository, and run command :
  ```bash
  # Generate lib
  ./configure --enable-static --disable-shared --prefix=$PWD/build/ && make && make install
  ``` 
4. Récupérer la librairie depuis le repo : ./build/lib/ (libprotobuf-c.a) <br />
   Récupérer le dossier include (.h) depuis le repo : ./build/include/ <br /><br />
   
RCENet :
1. Télécharger le repository de la dernière release : https://github.com/CrzGames/Crzgames_RCENet/releases (librcenet-linux.tar.gz)
2. Récupérer les fichiers include dans le dossier : ./linux/x86_64/include/ du dossier télécharger précédemment
3. Récupérer la librairie (librcenet.a) depuis le dossier : ./linux/x86_64/lib/ du dossier télécharger précédemment

<br /><br /><br /><br />


## Signed Executable :
1. Une clé de signature doit être préparée. Un nouveau peut être généré en utilisant (si c'est la première fois) :
  ```bash
  # Il faudra installer le package avant cela
  sudo apt-get install gnupg2 -y

  # Puis générer une key
  gpg2 --full-gen-key
  ```
2. Lister les clé de signature sur le système hôte :
  ```bash
  gpg2 --list-keys
  ```
3. Si besoin, importez votre clé de signature GPG dans GPG2 si ce n'est pas déjà fait. Vous pouvez le faire en utilisant la commande suivante :
  ```bash
  gpg2 --import /chemin/vers/votre/clé/publique
  ```
4. Signed binary *.AppImage :
  ```bash
  gpg2 --output /chemin/vers/votre/MyExecutable.AppImage --sign /chemin/vers/votre/MyExecutable.AppImage
  ```
5. Verify binary signature :
  ```bash
  gpg2 --verify MyExecutable.AppImage.sig MyExecutable.AppImage
  ```

<br /><br />

## Generate .AppImage :
1. Download AppImageTool AND Create an AppImage from a binary :
 ```bash
  # Download AppImageTool 
  wget https://github.com/AppImage/AppImageKit/releases/download/continuous/appimagetool-x86_64.AppImage
  chmod a+x appimagetool-x86_64.AppImage
  
  # Create AppImage from binary
  ./appimagetool-x86_64.AppImage myapp myapp.AppImage --appimage-extract-and-run --desktop-file myapp.desktop
  chmod a+x myapp.AppImage
  ```
