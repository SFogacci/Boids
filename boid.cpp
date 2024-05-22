// #include "boid.hpp"
// namespace bd {

// auto Boid::isClose(Boid const& b, float d) const
// {
//   auto distance = norm((b.getPosition() - this->position_));
//   return distance < d; //&& distance != 0; non considera se stesso un vicino
//                        // ma potrebbe evitare un altro nello
//                        // stesso posto
// }

// Vector Flock::separation(bd::Boid const& b, float ds, float s) const
// {
//   Vector correction;
//   for (auto const& other : flock_) {
//     if (b.isClose(other, ds)) {
//       correction +=
//           other.getPosition()
//           - b.getPosition(); // da migliorare evitando il boid stesso a
//           priori
//     }
//   }
//   return -s * correction;
// }

// Vector Flock::alignment(bd::Boid const& b, float d, float a) const
// {
//   Vector sumVel;
//   int size{};
//   for (auto const& other : flock_) {
//     if (b.isClose(other, d)) {
//       sumVel += other.getVelocity();
//       ++size;
//     }
//   }
//   Vector correction;
//   if (size != 1) {
//     correction = (sumVel - b.getVelocity())
//                / (size - 1); // da migliorare evitando il boid stesso a
//                priori
//   } // ho messo un assert per la divisione per 0, da migliorare
//   return a * correction;
// }

// Vector Flock::cohesion(bd::Boid const& b, float d, float c) const
// {
//   Vector sumPos;
//   int size{};
//   for (auto const& other : flock_) {
//     if (b.isClose(other, d)) {
//       sumPos += other.getPosition();
//       ++size;
//     }
//   }
//   Vector correction;
//   if (size != 1) {
//     auto cmPos = (sumPos - b.getPosition()) / (size - 1);
//     correction = cmPos - b.getPosition();
//   } // ho messo un assert per la divisione per 0, da migliorare
//   return c * correction;
// }

#include "boid.hpp"
namespace bd {

bool Boid::isClose(bd::Boid const& b, float d) const
{
  auto distance = norm((b.getPosition() - position_));
  return distance < d; //&& distance != 0; non considera se stesso un vicino
                       // ma potrebbe evitare un altro nello
                       // stesso posto
}

std::vector<Boid> Flock::evolution()
{
  std::vector<bd::Boid> modified_flock;
  modified_flock.reserve(size_);

  for (auto const& boid : flock_) {
    Vector separation{0.f, 0.f};
    Vector alignment;
    Vector cohesion;
    Vector sumVel{0.f, 0.f};
    Vector sumPos{0.f, 0.f};
    float neighbours{};
    for (auto const& other : flock_) {
      if (&other != &boid) {
        if (boid.isClose(other, d)) {
          sumPos += other.getPosition();
          sumVel += other.getVelocity();
          ++neighbours;
        }

        if (boid.isClose(other, ds)) {
          separation += other.getPosition();
        }
      }
    }
    if (neighbours != 0.f) {
      alignment = sumVel / neighbours;
      cohesion  = (sumPos / neighbours) - boid.getPosition();
    }

    Vector newVel =
        boid.getVelocity() + a * alignment + c * cohesion + -s * separation;
    // Vector newPos = boid.getPosition() + newVel;

    Boid modified_boid(newVel, boid.getPosition() + newVel);
    modified_flock.push_back(modified_boid);
  }
  return modified_flock;
}
} // namespace bd
// std::vector<Boid> Flock::evolution()
// {
//   std::vector<bd::Boid> modified_flock(size_);

//   for (auto const& boid : flock_) {
//     Vector separation;
//     Vector alignment;
//     Vector cohesion;
//     Vector sumVel;
//     Vector sumPos;
//     float neighbours{};
//     for (auto const& other : flock_) {
//       if (&other != &boid) {
//         if (boid.isClose(other, d)) {
//           sumPos += other.getPosition();
//           sumVel += other.getVelocity();
//           ++neighbours;
//         }

//         if (neighbours != 0.f) {
//           alignment = a * sumVel / (neighbours);
//           cohesion  = sumPos / (neighbours)-boid.getPosition();
//         }

//         if (boid.isClose(other, ds)) {
//           separation += other.getPosition();
//         }
//         separation = -s * separation;
//       }
//     }

//     Vector newVel = boid.getVelocity() + alignment + cohesion + separation;
//     Vector newPos = boid.getPosition() + newVel;

//     Boid modified_boid(newVel, newPos);
//     modified_flock.push_back(modified_boid);
//   }
//   return modified_flock;
// }
// } // namespace bd

// // namespace bd