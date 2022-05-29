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
        //耕地
        farmland,
        // 草ブロック
        grassBlock,
        // 石
        stone,
        // 丸石
        cobbleStone,
        // 磨かれたブラックストーンレンガ
        polishedBlackstoneBricks,
        //ネザーレンガ
        netherBricks,
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
        quartzStairs,
        // 鉄ブロック
        ironBlock,
        // 金ブロック
        goldBlock,
        // ダイアモンドブロック
        diamondBlock,

        /***** ハーフブロック *****/
        //ネザーレンガのハーフブロック
        netherBrickSlab,
        //滑らかなクォーツのハーフブロック
        smoothQuartzSlab,
        
        /***** 木材 *****/
        // オークの木材
        oakPlanks,
        // 白樺の木材
        birchPlanks,

        /***** 看板 *****/
        //オークの看板
        oakSign,
        
        /***** 壁付き看板 *****/
        //壁付のオークの看板
        oakWallSign,

        /***** 階段 *****/
        // なめらかなクォーツの階段
        smoothQuartzStairs,
        //ネザーレンガの階段
        netherBrickStairs,
        
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

        /***** トラップドア *****/
        //マツのトラップドア
        spruceTrapdoor,

        /***** フェンス *****/
        //ネザーレンガのフェンス
        netherBrickFence,
        //歪んだフェンス
        warpedFence,
        //オークのフェンス
        oakFence,

        /***** ゲート *****/
        // 歪んだフェンスゲート
        warpedFenceGate,

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
        jackOLantern,
        // シーランタン
        seaLantern,
        //レッドストーンランプ
        redstoneLamp,

        /***** レッドストーン系 *****/

        /********** 信号を伝えたりするもの **********/
        /*********************************レッドストーン以外で作られるもの*********************************/
        // レバー
        lever,
        
        /***** ボタン *****/
        // 石のボタン
        stoneButton,
        // 歪んだボタン
        warpedButton,
        
        /***** 感圧板 *****/
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
        //日照センサー
        daylightDetector,
        //ディスペンサー
        dispenser,
        //ホッパー
        hopper,

        
        /********** その他 **********/
        
        /***** ユーズフル *****/
        // クラフトテーブル
        craftingTable,
        // かまど
        furnace,
        // 燻製機
        smoker,
        // 溶鉱炉
        blastFurnace,
        // 製図台
        cartographyTable,
        // 矢細工台
        fletchingTable,
        // 砥石
        grindstone,
        // 鍛治台
        smithingTable,
        // 石切台
        stonecutter,
        // 金床
        anvil,
        
        // ジュークボックス
        jukebox,
        // エンダーチェスト
        enderChest,
        
        
        /***** その他 *****/
        // スポナー（豚）
        spawner,
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
        whiteCarpet,
        //チェスト
        chest,
        // 小麦の種
        wheat,
        //人参
        carrots,
        //じゃがいも
        potatoes,
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
    
    namespace Command {
        std::string itemInBox(
                              const WN::Vec3 &posi,
                              int containerPosition,
                              std::string item,
                              int numberOfItems
                              );
    }
}


#endif /* Minecraft_hpp */
