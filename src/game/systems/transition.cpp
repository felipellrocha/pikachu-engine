#include "transition.h"

void TransitionSystem::update(float dt) {
  for (auto transition : game->incoming) {
    transition->id = game->numTransitions++;
    game->transitions.insert(transition);
    transition->begin(manager, game);
  }
  game->incoming.clear();

  for (auto transition : game->transitions) {
    bool result = transition->tick(manager, game, dt);

    if (result) {
      game->outgoing.push_front(transition);
    }
  }

  for (auto transition : game->outgoing) {
    Transition* next = transition->end(manager, game);
    if (next) game->incoming.push_front(next);
    game->transitions.erase(transition);
  }

  game->outgoing.clear();
}
