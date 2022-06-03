//
//  Minecraft.cpp
//  GDMC_CLIENT
//
//  Created by 渡辺奈央騎 on 2021/12/17.
//

#include "Minecraft.hpp"

std::string Minecraft::getMinecraftBlockName(MinecraftBlock block, std::string addition) {
    
    std::string blockName = "minecraft:";
    
    switch (block) {
        /***** 気体 *****/
        case Minecraft::MinecraftBlock::air:
            blockName += "air";
            break;

        /***** 液体 *****/
        case Minecraft::MinecraftBlock::water:
            blockName += "water";
            break;
        
        case Minecraft::MinecraftBlock::flowingWater:
            blockName += "flowing_water";
            break;

        case Minecraft::MinecraftBlock::lava:
            blockName += "lava";
            break;

        case Minecraft::MinecraftBlock::flowingLava:
            blockName += "flowing_lava";
            break;
            
        /***** 固体 *****/

        /***** 石材 *****/
        case Minecraft::MinecraftBlock::dirt:
            blockName += "dirt";
            break;

        case Minecraft::MinecraftBlock::farmland:
            blockName += "farmland";
            break;
        
        case Minecraft::MinecraftBlock::grassBlock:
            blockName += "grass_block";
            break;
            
        case Minecraft::MinecraftBlock::stone:
            blockName += "stone";
            break;
            
        case Minecraft::MinecraftBlock::cobbleStone:
            blockName += "cobblestone";
            break;
            
        case Minecraft::MinecraftBlock::polishedBlackstoneBricks:
            blockName += "polished_blackstone_bricks";
            break;
            
        case Minecraft::MinecraftBlock::netherBricks:
            blockName += "nether_bricks";
            break;

        case Minecraft::MinecraftBlock::prismarineWall:
            blockName += "prismarine_wall";
            break;
        
        case Minecraft::MinecraftBlock::magmaBlock:
            blockName += "magma_block";
            break;

        case Minecraft::MinecraftBlock::soulSand:
            blockName += "soul_sand";
            break;

        /***** ガラス類 *****/
        case Minecraft::MinecraftBlock::glass:
            blockName += "glass";
            break;
            
        /*****コンクリート類 *****/
        case Minecraft::MinecraftBlock::whiteConcrete:
            blockName += "white_concrete";
            break;
        
        case Minecraft::MinecraftBlock::grayConcrete:
            blockName += "gray_concrete";
            break;
        
        case Minecraft::MinecraftBlock::lightGrayConcrete:
            blockName += "light_gray_concrete";
            break;
            
        /*****彩釉テラコッタ類 *****/
        case Minecraft::MinecraftBlock::blueGlazedTerracotta:
            blockName += "blue_glazed_terracotta";
            break;
            
        /***** 鉱材 *****/
        case Minecraft::MinecraftBlock::quartzBlock:
            blockName += "quartz_block";
            break;
            
        case Minecraft::MinecraftBlock::smoothQuartz:
            blockName += "smooth_quartz";
            break;
            
        case Minecraft::MinecraftBlock::quartzStairs:
            blockName += "quartz_stairs";
            break;

        case Minecraft::MinecraftBlock::ironBlock:
            blockName += "iron_block";
            break;
            
        case Minecraft::MinecraftBlock::goldBlock:
            blockName += "gold_block";
            break;
            
        case Minecraft::MinecraftBlock::diamondBlock:
            blockName += "diamond_block";
            break;

        /***** ハーフブロック *****/
        case Minecraft::MinecraftBlock::netherBrickSlab:
            blockName += "nether_brick_slab";
            break;

        case Minecraft::MinecraftBlock::smoothQuartzSlab:
            blockName += "smooth_quartz_slab";
            break;

        /***** 階段 *****/
        case Minecraft::MinecraftBlock::smoothQuartzStairs:
            blockName += "smooth_quartz_stairs";
            break;

        case Minecraft::MinecraftBlock::netherBrickStairs:
            blockName += "nether_brick_stairs";
            break;

        /***** 木材 *****/
        case Minecraft::MinecraftBlock::oakPlanks:
            blockName += "oak_planks";
            break;
            
        case Minecraft::MinecraftBlock::birchPlanks:
            blockName += "birch_planks";
            break;
            
        /***** 看板 *****/
        case Minecraft::MinecraftBlock::oakSign:
            blockName += "oak_sign";
            break;
            
        /***** 壁付き看板 *****/
        case Minecraft::MinecraftBlock::oakWallSign:
            blockName += "oak_wall_sign";
            break;
        
        /***** ドア *****/
        case Minecraft::MinecraftBlock::ironDoor:
            blockName += "iron_door";
            break;
            
        case Minecraft::MinecraftBlock::oakDoor:
            blockName += "oak_door";
            break;
            
        case Minecraft::MinecraftBlock::spruceDoor:
            blockName += "spruce_door";
            break;
            
        case Minecraft::MinecraftBlock::birchDoor:
            blockName += "birch_door";
            break;
            
        case Minecraft::MinecraftBlock::jungleDoor:
            blockName += "jungle_door";
            break;
            
        case Minecraft::MinecraftBlock::acaciaDoor:
            blockName += "acacia_door";
            break;
            
        case Minecraft::MinecraftBlock::darkOakDoor:
            blockName += "dark_oak_door";
            break;
            
        case Minecraft::MinecraftBlock::crimsonDoor:
            blockName += "crimson_door";
            break;
            
        case Minecraft::MinecraftBlock::warpedDoor:
            blockName += "warped_door";
            break;

        //*****トラップドア *****/
        //マツのトラップドア
        case Minecraft::MinecraftBlock::spruceTrapdoor:
            blockName += "spruce_trapdoor";
            break;

        /***** フェンス *****/
        case Minecraft::MinecraftBlock::netherBrickFence:
            blockName += "nether_brick_fence";
            break;
            
        case Minecraft::MinecraftBlock::warpedFence:
            blockName += "warped_fence";
            break;

        case Minecraft::MinecraftBlock::oakFence:
            blockName += "oak_fence";
            break;

        /***** ゲート *****/
        case Minecraft::MinecraftBlock::warpedFenceGate:
            blockName += "warped_fence_gate";
            break;
            
        /***** 光源 *****/
        case Minecraft::MinecraftBlock::torch:
            blockName += "torch";
            break;
            
        case Minecraft::MinecraftBlock::wallTorch:
            blockName += "wall_torch";
            break;
            
        case Minecraft::MinecraftBlock::soulTorch:
            blockName += "soul_torch";
            break;
            
        case Minecraft::MinecraftBlock::soulWallTorch:
            blockName += "soul_wall_torch";
            break;
            
        case Minecraft::MinecraftBlock::lantern:
            blockName += "lantern";
            break;
            
        case Minecraft::MinecraftBlock::soulLantern:
            blockName += "soul_lantern";
            break;
            
        case Minecraft::MinecraftBlock::glowstone:
            blockName += "glowstone";
            break;
            
        case Minecraft::MinecraftBlock::jackOLantern:
            blockName += "jack_o_lantern";
            break;
        case Minecraft::MinecraftBlock::seaLantern:
            blockName += "sea_lantern";
            break;
            
        case Minecraft::MinecraftBlock::redstoneLamp:
            blockName += "redstone_lamp";
            break;
        /***** レッドストーン系 *****/

        /********** 信号を伝えたりするもの **********/
            
        /*********************************レッドストーン以外で作られるもの*********************************/
        case Minecraft::MinecraftBlock::lever:
            blockName += "lever";
            break;
            
        /***** ボタン *****/
        case Minecraft::MinecraftBlock::stoneButton:
            blockName += "stone_button";
            break;
            
        case Minecraft::MinecraftBlock::warpedButton:
            blockName += "warped_button";
            break;
            
        /***** 感圧板 *****/
        case Minecraft::MinecraftBlock::stonePressurePlate:
            blockName += "stone_pressure_plate";
            break;
            
        case Minecraft::MinecraftBlock::warpedPressurePlate:
            blockName += "warped_pressure_plate";
            break;
            
        case Minecraft::MinecraftBlock::polishedBlackstonePressurePlate:
            blockName += "polished_blackstone_pressure_plate";
            break;
            
        /*********************************レッドストーンで作られるもの*********************************/
        case Minecraft::MinecraftBlock::redstoneWire:
            blockName += "redstone_wire";
            break;
            
        case Minecraft::MinecraftBlock::redstoneTorch:
            blockName += "redstone_torch";
            break;
            
        case Minecraft::MinecraftBlock::redstoneWallTorch:
            blockName += "redstone_wall_torch";
            break;
            
        case Minecraft::MinecraftBlock::repeater:
            blockName += "repeater";
            break;
            
        case Minecraft::MinecraftBlock::comparator:
            blockName += "comparator";
            break;
            
        /********** レッドストーン信号で動く物 **********/
        case Minecraft::MinecraftBlock::piston:
            blockName += "piston";
            break;
            
        case Minecraft::MinecraftBlock::stickyPiston:
            blockName += "sticky_piston";
            break;
            
        case Minecraft::MinecraftBlock::poweredRail:
            blockName += "powered_rail";
            break;
            
        case Minecraft::MinecraftBlock::detectorRail:
            blockName += "detector_rail";
            break;
            
        case Minecraft::MinecraftBlock::observer:
            blockName += "observer";

        case Minecraft::MinecraftBlock::daylightDetector:
            blockName += "daylight_detector";

            break;

        case Minecraft::MinecraftBlock::dispenser:
            blockName += "dispenser";
            break;
        
        case Minecraft::MinecraftBlock::hopper:
            blockName += "hopper";
            break;

        /********** その他 **********/
        /***** ユーズフル *****/
        case Minecraft::MinecraftBlock::craftingTable:
            blockName += "crafting_table";
            break;
            
        case Minecraft::MinecraftBlock::furnace:
            blockName += "furnace";
            break;
            
        case Minecraft::MinecraftBlock::smoker:
            blockName += "smoker";
            break;
            
        case Minecraft::MinecraftBlock::blastFurnace:
            blockName += "blast_furnace";
            break;
            
        case Minecraft::MinecraftBlock::cartographyTable:
            blockName += "cartography_table";
            break;
            
        case Minecraft::MinecraftBlock::fletchingTable:
            blockName += "fletching_table";
            break;
            
        case Minecraft::MinecraftBlock::grindstone:
            blockName += "grindstone";
            break;
            
        case Minecraft::MinecraftBlock::smithingTable:
            blockName += "smithing_table";
            break;
            
        case Minecraft::MinecraftBlock::stonecutter:
            blockName += "stonecutter";
            break;
            
        case Minecraft::MinecraftBlock::anvil:
            blockName += "anvil";
            break;
            
        case Minecraft::MinecraftBlock::jukebox:
            blockName += "jukebox";
            break;
            
        case Minecraft::MinecraftBlock::enderChest:
            blockName += "ender_chest";
            break;
            
        case Minecraft::MinecraftBlock::enchantingTable:
            blockName += "enchanting_table";
            break;
            
        /***** ベッド *****/
        case Minecraft::MinecraftBlock::whiteBed:
            blockName += "white_bed";
            break;
            
        case Minecraft::MinecraftBlock::magentaBed:
            blockName += "magenta_bed";
            break;
            
        /***** その他 *****/
        case Minecraft::MinecraftBlock::spawner:
            blockName += "spawner";
            break;
            
        case Minecraft::MinecraftBlock::rail:
            blockName += "rail";
            break;
            
        case Minecraft::MinecraftBlock::minecart:
            blockName += "minecart";
            break;
            
        case Minecraft::MinecraftBlock::beacon:
            blockName += "beacon";
            break;
        
        case Minecraft::MinecraftBlock::bookshelf:
            blockName += "bookshelf";
            break;

        case Minecraft::MinecraftBlock::chain:
            blockName += "chain";
            break;

        case Minecraft::MinecraftBlock::whiteCarpet:
            blockName += "white_carpet";
            break;

        case Minecraft::MinecraftBlock::chest:
            blockName += "chest";
            break;
        
        case Minecraft::MinecraftBlock::wheat:
            blockName += "wheat";
            break;

        case Minecraft::MinecraftBlock::carrots:
            blockName += "carrots";
            break;

        case Minecraft::MinecraftBlock::potatoes:
            blockName += "potatoes";
            break;

        default:
            blockName += "air";
            break;
    }
    
    if (addition != std::string()) {
        blockName += "[";
        blockName += addition;
        blockName += "]";
    }
    
    blockName += "\n";
    
    return blockName;
}

Minecraft::blockInfo::blockInfo(){
    this->angle = nullptr;
}
Minecraft::blockInfo::~blockInfo(){
    this->angle = nullptr;
}

Minecraft::blockInfo::blockInfo(WN::position x, WN::position y, WN::position z, MinecraftBlock block, std::string addition) {
    this->position.x = x;
    this->position.y = y;
    this->position.z = z;
    this->block = block;
    this->addition = addition;
    this->angle = nullptr;
}

Minecraft::blockInfo::blockInfo(WN::Vec3 vec, MinecraftBlock block, std::string addition) {
    this->position = vec;
    this->block = block;
    this->addition = addition;
    this->angle = nullptr;
}

std::string Minecraft::blockInfo::getTildeText() {
    
    std::string pos = "~";
    
    pos += std::to_string(this->position.x);
    pos += " ~";
    pos += std::to_string(this->position.y);
    pos += " ~";
    pos += std::to_string(this->position.z);
    pos += " ";
    
    if (this->angle != nullptr) {
        if (this->addition != "") {
            addition += ",";
        }
        addition += "facing=" + WN::facingDirection(*(this->angle));
    }
    
    pos += Minecraft::getMinecraftBlockName(block, addition);
    
    return pos;
}

void Minecraft::blockInfo::setInfo(WN::Vec3 vec, MinecraftBlock block, std::string addition) {
    this->position = vec;
    this->block = block;
    this->addition = addition;
}

void Minecraft::initBlockInfoOf3D(blockInfoOf3D &object, const WN::Vec3 &size) {
    object.reserve(size.y);
    for (auto &block2d : object) {
        block2d.reserve(size.z);
        for (auto &block1d : block2d) {
            block1d.reserve(size.x);
        }
    }
    
    int height, depth, width;
    
    for (height = 0; height < size.y; ++height) {
        object.push_back(std::vector<std::vector<Minecraft::blockInfo>>());
        for (depth = 0; depth < size.z; ++depth) {
            object[height].push_back(std::vector<Minecraft::blockInfo>());
            for (width = 0; width < size.x; ++width) {
                object[height][depth].push_back(Minecraft::blockInfo(
                                                            width,
                                                            height,
                                                            depth,
                                                            MinecraftBlock::air,
                                                            ""
                                                            )
                                       );
            }
        }
    }
    
}

void Minecraft::initBlockInfoOf3D(blockInfoOf3D &object, const WN::Vec3 &size, const WN::Vec3 &center) {
    WN::Vec3 begPosi(
                     center.x - 1 * size.x / 2,
                     center.y - 1 * size.y / 2,
                     center.z - 1 * size.z / 2
                     );
    
    object.reserve(size.y);
    for (auto &block2d : object) {
        block2d.reserve(size.z);
        for (auto &block1d : block2d) {
            block1d.reserve(size.x);
        }
    }
    
    int height, depth, width;
    
    for (height = 0; height < size.y; ++height) {
        object.push_back(std::vector<std::vector<Minecraft::blockInfo>>());
        for (depth = 0; depth < size.z; ++depth) {
            object[height].push_back(std::vector<Minecraft::blockInfo>());
            for (width = 0; width < size.x; ++width) {
                object[height][depth].push_back(Minecraft::blockInfo(
                                                            begPosi.x + width,
                                                            height,
                                                            begPosi.z + depth,
                                                            MinecraftBlock::air,
                                                            ""
                                                            )
                                       );
            }
        }
    }
    
}

std::shared_ptr<WN::direction> Minecraft::glazedTerracottaFacing(int width, int depth, int height) {
    
    WN::EveryDirection directions = WN::EveryDirection();
    
    if (height % 2 == 0) {
        switch ((width + depth) % 4) {
            case 0:
                return directions.front;
                
            case 1:
                return directions.left;
                
            case 2:
                return directions.behind;
                
            case 3:
                return directions.right;
                
            default:
                return directions.front;
        }
    } else {
        switch ((width + depth) % 4 + 1) {
            case 0:
                return directions.behind;
                
            case 1:
                return directions.right;
                
            case 2:
                return directions.front;
                
            case 3:
                return directions.left;
                
            default:
                return directions.front;
        }
    }
}

std::string Minecraft::Command::itemInBox(
                                          const WN::Vec3 &posi,
                                          int containerPosition,
                                          std::string item,
                                          int numberOfItems
                                          ) {
    std::string command = std::string("replaceitem block ") +
        std::to_string(static_cast<int>(posi.x)) + " " +
        std::to_string(static_cast<int>(posi.y)) + " " +
        std::to_string(static_cast<int>(posi.z)) + " container." +
        std::to_string(containerPosition) + " " + item + " " +
        std::to_string(numberOfItems) + "\n";
    return command;
}
