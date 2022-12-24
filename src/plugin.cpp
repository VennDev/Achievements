#include <llapi/LoggerAPI.h>
#include <MC/CommandOrigin.hpp>
#include <MC/CommandOutput.hpp>
#include <MC/ItemStack.hpp>
#include <MC/Level.hpp>
#include <MC/Player.hpp>
#include <MC/Types.hpp>
#include <DynamicCommandAPI.h>
#include <GlobalServiceAPI.h>

#include "EventListener.h"
#include "PlayerData.h"
#include "version.h"

#define DATA_FOLDER "plugins\\Achievements"

extern Logger logger;

void PluginInit() {
    Logger logger(PLUGIN_NAME);
    logger.info("Plugin loaded!");

    if (!std::filesystem::is_directory(DATA_FOLDER)) {
        std::filesystem::create_directory(DATA_FOLDER);
    }

    initDB();
    logger.info("{}", getPointa(PointType::Mining));
    setPointa(PointType::Mining, 34);
    logger.info("{}", getPointa(PointType::Mining));
    logger.info("Database loaded!");

    eventListen();
    
    DynamicCommand::setup(
        /* name = */ "stats",
        /* description = */ "Get player's stats.",
        /* enums = */ {},
        /* params = */ {},
        /* overloads = */ {
            {},
        },
        /* callback = */ [](
            DynamicCommand const& command,
            CommandOrigin const& origin,
            CommandOutput& output,
            std::unordered_map<std::string, DynamicCommand::Result>& results
        ) {
            /* output.success(
                std::string("Your stats: \n") +
                std::string("Xp: ") + 
                std::to_string(getPoint(origin.getPlayer()))
            ); */
        }
    );
}
