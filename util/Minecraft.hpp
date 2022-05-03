//
//  Minecraft.hpp
//  GDMC_CLIENT
//
//  Created by 渡辺奈央騎 on 2021/12/17.
//

#ifndef Minecraft_hpp
#define Minecraft_hpp

#include <iostream>
#include <vector>
#include <memory>


#include "Position.hpp"


namespace Minecraft {

    enum class MinecraftBlock:int {
        /***** 気体 *****/
        // 空気
        air,

        /***** 液体 *****/
        // 水源
        water,
        // 水流
        flowingWater,
        // 溶岩源
        lava,
        // 溶岩流
        flowingLava,

        /***** 固体 *****/

        /***** 石材 *****/
        // 土
        dirt,
        // 草ブロック
        grassBlock,
        // 石
        stone,
        // 丸石
        cobbleStone,
        // 磨かれたブラックストーンレンガ
        polishedBlackstoneBricks,
        // プリズマリンの塀
        prismarineWall,
        
        /*****コンクリート類 *****/
        // 白色コンクリート
        whiteConcrete,
        // 灰色コンクリート
        grayConcrete,
        // 薄灰色コンクリート
        lightGrayConcrete,

        /***** ガラス類 *****/
        // 透明ガラスブロック
        glass,

        /***** 鉱材 *****/
        // クォーツブロック
        quartzBlock,
        // 滑らかなクォーツブロック
        smoothQuartz,
        // 鉄ブロック
        ironBlock,
        // 金ブロック
        goldBlock,
        // ダイアモンドブロック
        diamondBlock,

        /***** 木材 *****/
        // オークの木材
        oakPlanks,
        // 白樺の木材
        birchPlanks,
        
        /***** 階段 *****/
        // なめらかなクォーツの階段
        smoothQuartzStairs,
        
        /***** ドア *****/
        // 鉄のドア
        ironDoor,
        // オークのドア
        oakDoor,
        // マツのドア
        spruceDoor,
        // シラカバのドア
        birchDoor,
        // ジャングルのドア
        jungleDoor,
        // アカシアのドア
        acaciaDoor,
        // ダークオークのドア
        darkOakDoor,
        // 真紅のドア
        crimsonDoor,
        // 歪んだドア
        warpedDoor,
        

        /***** その他 *****/

        /***** 光源 *****/
        // トーチ
        torch,
        // 壁付きのトーチ
        wallTorch,
        // ソウルトーチ
        soulTorch,
        // 壁付きのソウルトーチ
        soulWallTorch,
        // ランタン
        lantern,
        // ソウルランタン
        soulLantern,
        // グロウストーン
        glowstone,

        /***** レッドストーン系 *****/

        /********** 信号を伝えたりするもの **********/
        /*********************************レッドストーン以外で作られるもの*********************************/
        // レバー
        lever,
        // 石の感圧板
        stonePressurePlate,
        
        /*********************************レッドストーンで作られるもの*********************************/
        // レッドストーンワイヤー
        redstoneWire,
        // レッドストーントーチ
        redstoneTorch,
        // 壁付きのレッドストーントーチ
        redstoneWallTorch,
        // リピーター
        repeater,
        // レッドストーンコンパレーター
        comparator,

        /********** レッドストーン信号で動く物 **********/
        // ピストン
        piston,
        // 粘着ピストン
        stickyPiston,
        // パワードレール
        poweredRail,
        // ディテクターレール（感知レール）
        detectorRail,

        /***** その他 *****/
        // レール
        rail,
        // トロッコ
        minecart,
        // ビーコン
        beacon,
    };

    std::string getMinecraftBlockName(MinecraftBlock block, std::string addition);
    
    struct blockInfo {
        WN::Vec3 position;
        MinecraftBlock block;
        std::string addition;
        std::shared_ptr<WN::direction> angle;

        // コンストラクタ
        blockInfo();
        blockInfo(WN::position x, WN::position y, WN::position z, MinecraftBlock block, std::string addition);
        blockInfo(WN::Vec3 vec, MinecraftBlock block, std::string addition);
        // デストラクタ
        ~blockInfo();
        
        // チルダ形式の情報を入手
        std::string getTildeText();
        // 情報をセットする関数
        void setInfo(WN::Vec3 vec, MinecraftBlock block, std::string addition);
    };

    using blockInfoOf3D = std::vector<std::vector<std::vector<blockInfo> > >;
    void initBlockInfoOf3D(blockInfoOf3D &object, const WN::Vec3 &size);
    void initBlockInfoOf3D(blockInfoOf3D &object, const WN::Vec3 &size, const WN::Vec3 &center);
}


#endif /* Minecraft_hpp */
