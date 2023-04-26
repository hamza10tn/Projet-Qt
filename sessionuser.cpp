#include "sessionuser.h"
//variable de classe

SessionUser* SessionUser::Instance = nullptr;

SessionUser::SessionUser()
{
    ConnectedUser=nullptr;

}
//recuperi l emploues connecte
Employes* SessionUser::getConnectedUser() {
       return ConnectedUser;
   }

   // méthode pour définir l'employé connecté actuellement
void SessionUser::setConnectedUser(Employes* employe) {
       ConnectedUser = employe;
}
//trajaali l instance unique
SessionUser* SessionUser::getInstance()
{
            if(Instance==nullptr){
               Instance=new SessionUser();
            }

      return Instance;

}
