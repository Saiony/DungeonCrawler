#include "bonfire_scene.h"
#include "../Utility/custom_print.h"

dungeon_client::scene::bonfire_scene::bonfire_scene(std::shared_ptr<client> client_ptr): client_ptr_(std::move(client_ptr))
{
}

void dungeon_client::scene::bonfire_scene::print_header() const
{
    system("CLS");
    utility::custom_print::print_aligned("        .", 42);
    utility::custom_print::print_aligned("        .", 0);
    std::cout << std::endl;
    utility::custom_print::print_aligned("     . ( `  .", 42);
    utility::custom_print::print_aligned("     . ( `  .", 0);
    std::cout << std::endl;
    utility::custom_print::print_aligned("    ) `   `  `", 20);
    utility::custom_print::print_aligned("====================", 22);
    utility::custom_print::print_aligned("    ) `   `  `", 0);
    std::cout << std::endl;
    utility::custom_print::print_aligned("   (_(_`_ _)__)", 26);
    utility::custom_print::print_aligned("BONFIRE", 16);
    utility::custom_print::print_aligned("   (_(_`_ _)__)", 20);
    std::cout << std::endl;
    utility::custom_print::print_aligned("  (o)__________)", 20);
    utility::custom_print::print_aligned("====================", 22);
    utility::custom_print::print_aligned("  (o)__________)", 20);
    std::cout << std::endl;
    utility::custom_print::print_aligned(" (o)____________)", 42);
    utility::custom_print::print_aligned(" (o)____________)", 20);
    std::cout << std::endl << std::endl;
}

void dungeon_client::scene::bonfire_scene::show()
{
    print_header();

    client_ptr_->request_bonfire_story_teller([this](auto story_telling)
    {
        if (story_telling.story_teller.public_id != client_ptr_->get_player().public_id)
        {
            client_ptr_->subscribe_bonfire_result([this](auto callback)
            {
                print_bonfire_result(callback);
            });

            std::cout << "Story teller: " + story_telling.story_teller.name << std::endl;
            handle_wrong_player_input();
            return;
        }

        std::cout << "You are the story teller..." << std::endl;
        std::cout << "Please select the attribute you want the party to upgrade: " << std::endl;

        std::ranges::for_each(story_telling.player_stats, [](auto stats)
        {
            utility::custom_print::print_aligned("- " + stats.name, 20);
            std::cout << std::endl;
        });

        handle_stat_input(story_telling);
    });
}


void dungeon_client::scene::bonfire_scene::handle_wrong_player_input()
{
    client_ptr_->read_input([this](const std::string& input)
    {
        std::cout << "Sssshhhh... the story teller is thinking about a story..." << std::endl;
        handle_wrong_player_input();
    });
}

void dungeon_client::scene::bonfire_scene::handle_stat_input(domain::bonfire_story_telling story_telling)
{
    client_ptr_->read_input([this, &story_telling](const std::string& input)
    {
        const auto answer_it = std::ranges::find_if(story_telling.player_stats, [&input](auto stat)
        {
            return stat.name == input;
        });

        if (answer_it == std::end(story_telling.player_stats))
        {
            std::cout << std::endl << "Please type a valid stat" << std::endl;
            handle_stat_input(story_telling);
        }

        chosen_stat_ = (*answer_it);
        print_story_request(story_telling);
    });
}

void dungeon_client::scene::bonfire_scene::print_story_request(const domain::bonfire_story_telling& story_telling)
{
    print_header();
    std::cout << "\nNow it's time for you to tell a story that will inspire the others" << std::endl;
    std::cout << "If you're able to communicate with others using sounds, feel free to do so" << std::endl;
    std::cout << "You can tell any story, but here are some inspirations: " << std::endl;

    switch (chosen_stat_.id)
    {
    case dungeon_common::enums::creature_stat_types::attack_damage:
        {
            std::cout << "\t- A fight you needed to attack instead of defend" << std::endl;
            std::cout << "\t- That time you moved a giant rock" << std::endl;
            std::cout << "\t- When you killed a giant bear" << std::endl;
            break;
        }
    case dungeon_common::enums::creature_stat_types::ability_power:
        {
            std::cout << "\t- The first time you casted a fireball" << std::endl;
            std::cout << "\t- Explain how you channel magic" << std::endl;
            std::cout << "\t- When you visited the fae realm" << std::endl;
            break;
        }
    case dungeon_common::enums::creature_stat_types::max_health:
        {
            std::cout << "- A time you almost died" << std::endl;
            std::cout << "- When you found the cure of a disease" << std::endl;
            std::cout << "- When you needed to be resilient" << std::endl;
            break;
        }
    default:
        {
            throw std::exception("Invalid stat");
        }
    }

    handle_story_input(story_telling);
}

void dungeon_client::scene::bonfire_scene::handle_story_input(const domain::bonfire_story_telling& story_telling)
{
    client_ptr_->read_input([this, &story_telling](const std::string& input)
    {
        if (std::size(input) > story_telling.max_characters)
        {
            std::cout << "Sorry, your story needs to have [" + std::to_string(story_telling.max_characters) + "] maximum characters";
            handle_story_input(story_telling);
        }

        client_ptr_->send_bonfire_story(chosen_stat_, input, [this](auto callback)
        {
            print_bonfire_result(callback);
        });
    });
}

void dungeon_client::scene::bonfire_scene::print_bonfire_result(const domain::bonfire_result& bonfire_result) const
{
    print_header();
    std::cout << "\n" + bonfire_result.story_teller.name + " clears the throat and says...\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << bonfire_result.story << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));

    print_header();
    std::cout << "\nEveryone feels more motivated after this:" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "\t-HP recovered" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "\t-" + bonfire_result.upgraded_stat.name + " increased" << std::endl << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));

    std::ranges::for_each(bonfire_result.level_up_log, [](auto log)
    {
        std::cout << log << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    });

    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "\nThe bonfire is extinguished and you continue your journey..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    on_scene_ended_callback_();
}
