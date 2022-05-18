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
        //ネザーレンガ
        nether_bricks,
        // プリズマリンの塀
        prismarineWall,
        //マグマブロック
        magmaBlock,
        //ソウルサンド
        soulSand,
        
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
        // クォーツの階段
        quartz_stairs,
        // 鉄ブロック
        ironBlock,
        // 金ブロック
        goldBlock,
        // ダイアモンドブロック
        diamondBlock,

        /***** ハーフブロック *****/
        //ネザーレンガのハーフブロック
        nether_brick_slab,

        /***** 木材 *****/
        // オークの木材
        oakPlanks,
        // 白樺の木材
        birchPlanks,

        /***** 看板 *****/
        //オークの看板
        oak_sign,

        /***** 階段 *****/
        // なめらかなクォーツの階段
        smoothQuartzStairs,
        //ネザーレンガの階段
        nether_brick_stairs,
        
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

        /***** フェンス *****/
        //ネザーレンガのフェンス
        nether_brick_fence,
        //歪んだフェンス
        warped_fence,
        //オークのフェンス
        oak_fence,

        /***** ゲート *****/
        // 歪んだフェンスゲート
        warpedFenceGate,
        

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
        // ジャックオランタン
        jack_o_lantern,
        // シーランタン
        seaLantern,
        //レッドストーンランプ
        redstoneLamp,

        /***** レッドストーン系 *****/

        /********** 信号を伝えたりするもの **********/
        /*********************************レッドストーン以外で作られるもの*********************************/
        // レバー
        lever,
        // 石のボタン
        stone_button,
        // 石の感圧板
        stonePressurePlate,
        // 歪んだ感圧板
        warpedPressurePlate,
        // 磨かれたブラックストーンの感圧板
        polishedBlackstonePressurePlate,
        
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
        //オブザーバー
        observer,
        //月照センサー
        daylight_detector_inverted,

        /***** その他 *****/
        // レール
        rail,
        // トロッコ
        minecart,
        // ビーコン
        beacon,
        //本棚
        bookshelf,
        //鎖
        chain,
        //白のカーペット
        white_carpet,
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
