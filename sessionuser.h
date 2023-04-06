#ifndef SESSIONUSER_H
#define SESSIONUSER_H
#include "employes.h"

class SessionUser
{
public:
        static SessionUser* getInstance();


        // méthode pour récupérer l'employé connecté actuellement
        Employes* getConnectedUser();

        // méthode pour définir l'employé connecté actuellement
        void setConnectedUser(Employes* employe);

private :
    Employes* ConnectedUser;
    static SessionUser* Instance; // instance unique de SessionUser

    SessionUser();


};

#endif // SESSIONUSER_H
