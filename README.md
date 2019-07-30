# OpenMesh_samples
OpenMesh basic usage

# 環境構築

## インストーラーを使用する場合

OpenMeshのGitLabのリンク(https://www.graphics.rwth-aachen.de:9000/OpenMesh/OpenMesh#download-binaries)からインストーラーをダウンロードして実行する。

この方法ではリリース版のライブラリしかインストールされない。

## ソースからビルドする場合

cmakeとQtが無い場合は先にインストールしておくこと。

Qtは使用するコンパイラのbinのパスを通しておくとcmakeが自動で見つけてくれる。

ソースを任意のフォルダにクローンする。

```
C:\Users\nitta\Documents\GitLab>git clone https://www.graphics.rwth-aachen.de:9000/OpenMesh/OpenMesh.git
Cloning into 'OpenMesh'...
remote: Enumerating objects: 19584, done.
remote: Counting objects: 100% (19584/19584), done.
remote: Compressing objects: 100% (5235/5235), done.
remote: Total 19584 (delta 14114), reused 19502 (delta 14071)
Receiving objects: 100% (19584/19584), 9.15 MiB | 454.00 KiB/s, done.
Resolving deltas: 100% (14114/14114), done.
Checking out files: 100% (567/567), done.
```

クローンしたフォルダに移動し、build用のフォルダを作成、build内でcmakeコマンドを実行する。コンパイラは適当なもの(ここではVisual Studio 2017)を指定する。

```
C:\Users\nitta\Documents\GitLab>cd OpenMesh

C:\Users\nitta\Documents\GitLab\OpenMesh>md build

C:\Users\nitta\Documents\GitLab\OpenMesh>cd build

C:\Users\nitta\Documents\GitLab\OpenMesh\build>cmake .. -G"Visual Studio 15 2017 Win64"
-- Selecting Windows SDK version 10.0.17763.0 to target Windows 10.0.17134.
-- The C compiler identification is MSVC 19.16.27031.1
-- The CXX compiler identification is MSVC 19.16.27031.1
-- Check for working C compiler: C:/Program Files (x86)/Microsoft Visual Studio/2017/Community/VC/Tools/MSVC/14.16.27023/bin/Hostx86/x64/cl.exe
-- Check for working C compiler: C:/Program Files (x86)/Microsoft Visual Studio/2017/Community/VC/Tools/MSVC/14.16.27023/bin/Hostx86/x64/cl.exe -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Check for working CXX compiler: C:/Program Files (x86)/Microsoft Visual Studio/2017/Community/VC/Tools/MSVC/14.16.27023/bin/Hostx86/x64/cl.exe
-- Check for working CXX compiler: C:/Program Files (x86)/Microsoft Visual Studio/2017/Community/VC/Tools/MSVC/14.16.27023/bin/Hostx86/x64/cl.exe -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Found OpenGL: opengl32
-- Could NOT find Doxygen (missing: DOXYGEN_EXECUTABLE)

************************************************************
* ACG Buildsystem                                          *
*                                                          *
* Package : OpenMesh                                       *
* Version : 8.1                                            *
************************************************************
-- Configuring done
-- Generating done
-- Build files have been written to: C:/Users/nitta/Documents/GitLab/OpenMesh/build
```

一度cmakeのguiを起動し、オプションの設定を行う。

```
C:\Users\nitta\Documents\GitLab\OpenMesh\build>cmake-gui ..
```

必要なら以下の設定を変更する。

| 設定項目              | デフォルト値 |説明|
| --------------------- | ---- |---|
| OPENMESH_BUILD_SHARED | OFF |ON:DLL形式でビルドする|
|CMAKE_INSTALL_PREFIX|C:/Program Files/OpenMesh|ビルドファイルのインストールディレクトリ|

設定を変更した場合はgui上でgenerateを実行する。

コンパイラで指定したvisual studio 2017を管理者権限で起動して、`./build/OpenMesh.sln`ファイルを開く。

DebugとReleaseでコンパイルしたい方を選択(両方必要ならモード切り替えて再度同じ手順で実行する)し、ソリューションエクスプローラーでALL_INSTALLを選択。

メニューのビルド$\rightarrow$ALL_BUILDのビルドを実行。cmakeの設定に問題が無ければ、以下の出力が出てくる

```
========== ビルド: 18 正常終了、0 失敗、0 更新不要、0 スキップ ==========
```

その後、INSTALLを選択し、メニューのビルド$\rightarrow$INSTALLのビルドを実行。以下の出力になる。

```
========== ビルド: 2 正常終了、0 失敗、17 更新不要、0 スキップ ==========
```

./build/Build内にサンプルの実行ファイルがいくつか生成される。

---

# サンプルファイル

## tutorial_001_BuildingCube

https://www.openmesh.org/media/Documentations/OpenMesh-Doc-Latest/a04088.html

<img src="img/001_BuildingCube.png" width="100%">

公式サイトのチュートリアル最初のサンプル(https://www.openmesh.org/media/Documentations/OpenMesh-Doc-Latest/a04088.html)

CMakeLists.txtはチュートリアルではgitファイル内で使う方法しか書かれてないようだったため、新規で作成。

必要な箇所だけ抜粋すると以下のようになる。

```cmake:CMakeLists.txt
cmake_minimum_required( VERSION 3.6 )

# Create Project
get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME) # https://stackoverflow.com/questions/12344368/automatically-use-the-directory-as-the-project-name-in-cmake
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId} CXX)

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

# Find OpenMesh Package
set( OpenMesh_ROOT "C:/Program Files/OpenMesh")
find_package( OpenMesh REQUIRED )

set(SOURCE_FILES
   main.cpp
)
set(TARGET_LINK_LIBRARIES
   OpenMeshCore
   OpenMeshTools
)
# Add Executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Preprocessor Definitions
add_definitions(-D_USE_MATH_DEFINES) # Core/System/compiler.hhで定義が無いとエラーになる
target_link_libraries(${PROJECT_NAME} ${TARGET_LINK_LIBRARIES})

```

OpenMeshCoreとOpenMeshToolsにincludeパスとlibの設定がされている(`C:\Program Files\OpenMesh\share\OpenMesh\cmake\OpenMeshConfig.cmake`)ので、target_link_librariesだけで設定が完了する。

実行すると、立方体形状のoffファイルを生成する。

## tutorial_002_Iterators_Circulators

https://www.openmesh.org/media/Documentations/OpenMesh-Doc-Latest/a04089.html

|スムージング前|スムージング後|
|---|---|
|<img src="img/tutorial_002_Iterators_Circulators_1.PNG" width="100%" title="">|<img src="img/tutorial_002_Iterators_Circulators_2.PNG" width="100%" title="">|

全ての頂点について隣接するすべての頂点の座標平均を取り、そこに頂点を移動させる。

隣接頂点が不正(non manifold)の場合

- 2つ以上のポリゴンが頂点ひとつだけを共有している場合：`mesh.is_manifold(v_it)`でfalseを返す。circulatorは隣接頂点をすべて巡回する。
- 一つの辺が3つ以上のポリゴンで共有されている場合：頂点が自動的に複製されてnon-manifoldでない状態になる(各ポリゴンのつながりはすべて分離される)

## tutorial_003_CustomProp

https://www.openmesh.org/media/Documentations/OpenMesh-Doc-Latest/a04090.html

- custom properties
  - 頂点、面、辺、ハーフエッジに付随する任意のデータ型を追加できる
  - 曲率などの保存に使用できる
- iteratorを使わずにすべての頂点を巡回(for(auto: ~)使用)

## tutorial_004_STL_algorithms

https://www.openmesh.org/media/Documentations/OpenMesh-Doc-Latest/a04091.html



---

## 001_iterator_dump

読み込んだファイルの頂点とメッシュを巡回し、インデックスを出力する。隣接頂点・隣接面のインデックスも出力する。

