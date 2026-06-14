#include <iostream>

#include "if.h"
#include "messages.h"

void interface_machine::done()
{
    get_sender().send(messaging::close_queue());
}

messaging::sender   interface_machine::get_sender()
{
    return incoming;
}

void interface_machine::run()
{
    try {
        for(;;)
        {
            incoming.wait()
            .handle<issue_money>(
                [&](issue_money const& msg)
                {
                    std::lock_guard<std::mutex> lk(iom);
                    std::cout << "issuing"
                              << msg.amount<<std::endl;
                }
                )
                .handle<display_insufficient_funds>(
                    [&](display_insufficient_funds const& msg)
                    {
                        std::lock_guard<std::mutex> lk(iom);
                        std::cout<<"Insufficient funds"<<std::endl;
                    }
                    )
                .handle<display_enter_pin>(
                    [&](display_enter_pin const& msg)
                    {
                        std::lock_guard<std::mutex> lk(iom);
                        std::cout<< "Please enter your pin (0-9) "
                                  <<std::endl;
                    }
                    )
                .handle<display_enter_card>(
                    [&](display_enter_card const& msg)
                    {
                        std::lock_guard<std::mutex> lk(iom);
                        std::cout<<
                            "Please enter your card (I) "
                                  <<std::endl;
                    }
                    )
                .handle<display_balance>(
                    [&](display_balance const& msg)
                    {
                        std::lock_guard<std::mutex> lk(iom);
                        std::cout<<
                            "The balance of your account is "
                                  <<msg.amount  <<std::endl;
                    }
                    )
                .handle<display_withdrawal_options>(
                    [&](display_withdrawal_options const& msg)
                    {
                        std::lock_guard<std::mutex> lk(iom);
                        std::cout<< "Withdraw 50? (w)\n";
                        std::cout<< "Display balance? (b)\n";
                        std::cout<< "Cancel? (c)\n";
                    }
                    )
                .handle<display_withdrawal_cancelled>(
                    [&](display_withdrawal_cancelled const& msg)
                    {
                        std::lock_guard<std::mutex> lk(iom);
                        std::cout<<"Withdrawal cancelled.\n";
                    }
                    )
                .handle<display_pin_incorrect_message>(
                    [&](display_pin_incorrect_message const& msg)
                    {
                        std::lock_guard<std::mutex> lk(iom);
                        std::cout<<"Pin incorrect.\n";
                    }
                    )
                .handle<eject_card>(
                    [&](eject_card const& msg)
                    {
                        std::lock_guard<std::mutex> lk(iom);
                        std::cout<<"Ejecting card.\n";
                    }
                    );
        }
    } catch (messaging::close_queue const&) {
    }
}