#include <map>
#include <string>


#include <ftxui/component/input.hpp> // for InputBase
#include <ftxui/component/screen_interactive.hpp> // for ScreenInteractive

using std::wstring_view;

std::function<void()> g_QuitApp;
std::wstring g_currentCmdString;
auto g_cmdHistoryContainer = ftxui::Container::Vertical({});


std::pair<wstring_view, wstring_view> ParseLineIntoCommandAndArgs(const wstring_view & line)
{
    auto locationOfSpace = line.find_first_of(L" ", 0);

    if (locationOfSpace == wstring_view::npos)
    {
        return make_pair(line, wstring_view{});
    }
    else
    {
        auto cmd = wstring_view(line.data(), line.data() + locationOfSpace);
        auto args = wstring_view(line.data() + locationOfSpace + 1, line.data() + line.length());
        return make_pair(cmd, args);
    }
}


void AddLine(ftxui::Element && line)
{
    g_cmdHistoryContainer->Add(ftxui::Renderer([element = move(line)]{ return element; }));
}


void AddTextLine(const std::wstring & str)
{
    AddLine(ftxui::text(str));
}


void ProcessCommand(const std::wstring & commandString)
{
    std::map<std::wstring, std::function<void(const wstring_view &)>, std::less<>> commands;

    auto quitCmd = [](const wstring_view &) { g_QuitApp(); };

    commands[L"quit"] = quitCmd;
    commands[L"exit"] = quitCmd;

    commands[L"help"] = [](const wstring_view &)
    {
        AddTextLine(L"Type 'quit' or 'exit' to stop.");
    };

    // break into two
    auto [command, restOfCommand] = ParseLineIntoCommandAndArgs(commandString);

    auto iter = commands.find(command);

    if (iter != commands.cend())
    {
        iter->second(restOfCommand);
    }
}


auto RenderProcessStatusUI()
{
    using namespace ftxui;
    return window(
        text(L"Process Status"),
        vbox({
            hbox({
                text(L"Service") | size(WIDTH, EQUAL, 12),
                separator(),
                text(L"proc1") | size(WIDTH, EQUAL, 12) | bgcolor(Color::Red),
                separator(),
                text(L"proc2") | size(WIDTH, EQUAL, 12) | bgcolor(Color::Green),
                }),
            separator(),
            hbox({
                text(L"other") | size(WIDTH, EQUAL, 12),
                separator(),
                text(L"bob") | size(WIDTH, EQUAL, 12),
                separator(),
                text(L"") | size(WIDTH, EQUAL, 12),
                }),
            }));
}


auto RenderBoxGridUI()
{
    using namespace ftxui;
    return window(
        text(L"boxes"),
        vbox({
            hbox({
                text(L"x") | size(WIDTH, EQUAL, 2),
                separator(),
                text(L"x") | size(WIDTH, EQUAL, 2),
                separator(),
                text(L"x") | size(WIDTH, EQUAL, 2),
                separator(),
                text(L"x") | size(WIDTH, EQUAL, 2),
                separator(),
                text(L"x") | size(WIDTH, EQUAL, 2),
                separator(),
                text(L"x") | size(WIDTH, EQUAL, 2),
                separator(),
                text(L"x") | size(WIDTH, EQUAL, 2),
                separator(),
                text(L"x") | size(WIDTH, EQUAL, 2),
                separator(),
                text(L"x") | size(WIDTH, EQUAL, 2),
                separator(),
                text(L"x") | size(WIDTH, EQUAL, 2),
                }),
            separator(),
            hbox({
                text(L"x") | size(WIDTH, EQUAL, 2),
                separator(),
                text(L"x") | size(WIDTH, EQUAL, 2),
                separator(),
                text(L"x") | size(WIDTH, EQUAL, 2),
                separator(),
                text(L"x") | size(WIDTH, EQUAL, 2),
                separator(),
                text(L"x") | size(WIDTH, EQUAL, 2),
                separator(),
                text(L"x") | size(WIDTH, EQUAL, 2),
                separator(),
                text(L"x") | size(WIDTH, EQUAL, 2),
                separator(),
                text(L"x") | size(WIDTH, EQUAL, 2),
                separator(),
                text(L"x") | size(WIDTH, EQUAL, 2),
                separator(),
                text(L"x") | size(WIDTH, EQUAL, 2),
                }),
            separator(),
            hbox({
                text(L"x") | size(WIDTH, EQUAL, 2),
                separator(),
                text(L"x") | size(WIDTH, EQUAL, 2),
                separator(),
                text(L"x") | size(WIDTH, EQUAL, 2),
                separator(),
                text(L"x") | size(WIDTH, EQUAL, 2),
                separator(),
                text(L"x") | size(WIDTH, EQUAL, 2),
                separator(),
                text(L"x") | size(WIDTH, EQUAL, 2),
                separator(),
                text(L"x") | size(WIDTH, EQUAL, 2),
                separator(),
                text(L"x") | size(WIDTH, EQUAL, 2),
                separator(),
                text(L"x") | size(WIDTH, EQUAL, 2),
                separator(),
                text(L"x") | size(WIDTH, EQUAL, 2),
                }),
            separator(),
            hbox({
                text(L"x") | size(WIDTH, EQUAL, 2),
                separator(),
                text(L"x") | size(WIDTH, EQUAL, 2),
                separator(),
                text(L"x") | size(WIDTH, EQUAL, 2),
                separator(),
                text(L"x") | size(WIDTH, EQUAL, 2),
                separator(),
                text(L"x") | size(WIDTH, EQUAL, 2),
                separator(),
                text(L"x") | size(WIDTH, EQUAL, 2),
                separator(),
                text(L"x") | size(WIDTH, EQUAL, 2),
                separator(),
                text(L"x") | size(WIDTH, EQUAL, 2),
                separator(),
                text(L"x") | size(WIDTH, EQUAL, 2),
                separator(),
                text(L"x") | size(WIDTH, EQUAL, 2),
                }),
            separator(),
            hbox({
                text(L"x") | size(WIDTH, EQUAL, 2),
                separator(),
                text(L"x") | size(WIDTH, EQUAL, 2),
                separator(),
                text(L"x") | size(WIDTH, EQUAL, 2),
                separator(),
                text(L"x") | size(WIDTH, EQUAL, 2),
                separator(),
                text(L"x") | size(WIDTH, EQUAL, 2),
                separator(),
                text(L"x") | size(WIDTH, EQUAL, 2),
                separator(),
                text(L"x") | size(WIDTH, EQUAL, 2),
                separator(),
                text(L"x") | size(WIDTH, EQUAL, 2),
                separator(),
                text(L"x") | size(WIDTH, EQUAL, 2),
                separator(),
                text(L"x") | size(WIDTH, EQUAL, 2),
                }),
            separator(),
            }));
}


void HandleCommandEnter()
{
    AddLine(ftxui::text(std::format(L">{}", g_currentCmdString)) | ftxui::dim);
    ProcessCommand(g_currentCmdString);
    g_currentCmdString = L"";
}


int main(int argc, char* const argv[])
{
    using namespace ftxui;

    g_cmdHistoryContainer->Add(Renderer([] {
        return text(L"Welcome!");
        }));

    std::wstring command;

    auto cmdInput = Input(&g_currentCmdString, "enter command");

    InputBase::From(cmdInput)->on_enter = HandleCommandEnter;

    auto layout = Container::Vertical({
        g_cmdHistoryContainer,
        cmdInput,
        });

    auto component = Renderer(layout,
        [&] {
            return hbox({
                vbox({
                    g_cmdHistoryContainer->Render() | yframe  | flex_grow,
                    separator(),
                    cmdInput->Render(),
                    }) | border | flex_grow,
                vbox({
                    RenderProcessStatusUI(),
                    align_right(RenderBoxGridUI() | flex_shrink),
                    filler(),
                    }),
                });
        });

    auto screen = ScreenInteractive::Fullscreen();
    g_QuitApp = screen.ExitLoopClosure();
    screen.Loop(component);

    return 0;
}
