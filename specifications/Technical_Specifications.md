# Apocalyptic Soulmate - Technical Specifications

![-](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/aqua.png)

<details>
<summary>📖 Table of content</summary>

- [Apocalyptic Soulmate - Technical Specifications](#apocalyptic-soulmate---technical-specifications)
  - [I. Overview](#i-overview)
    - [A. Project Introdction](#a-project-introdction)
    - [B. Team Development](#b-team-development)
  - [III. Design](#iii-design)
    - [A. Background](#a-background)
    - [B. Characters](#b-characters)
    - [C. Items](#c-items)
  - [II. Implementation](#ii-implementation)
    - [A. Characters](#a-characters)
    - [B. Items](#b-items)

</details>

![-](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/aqua.png)

| | |
| ----- | ----- |
| Author(s) | Grégory PAGNOUX |
| Reviewer(s) | Mathis LEBEL, Séréna BAVAROIS |
| Created on | 21/03/2024 |
| Last updated | 22/03/2024 |
|  |  |

![-](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/aqua.png)

## I. Overview

### A. Project Introdction

You are the last man in the world and you need to escape zombies and find your soulmate that you loose at the beginning of the invasion.
For that, you need to find a door to pass each room and to be in secure place.
Every two levels, you find a boss to earn new equipment like weapons, shield, portals, etc.

Can you find your lost love?

### B. Team Development

| PERSON | ROLE | GITHUB | MAIL |
| - | - | - | - |
| <img src="https://avatars.githubusercontent.com/u/114397869?v=4" alt="Grégory PAGNOUX" width="75px"> <br> Grégory PAGNOUX | Writter Manager / Developper | [Grégory PAGNOUX profile](https://github.com/Gregory-Pagnoux) | [gregory.pagnoux@algosup.com](mailto:gregory.pagnoux@algosup.com) |
| <img src="https://avatars.githubusercontent.com/u/145991354?v=4" alt="Mathis LEBEL" width="75px"> <br> Mathis LEBEL | Developper Manager | [Mathis LEBEL profile](https://github.com/mathislebel)|  [mathis.lebel@algosup.com](mailto:mathis.lebel@algosup.com) |
| <img src="https://avatars.githubusercontent.com/u/145995847?v=4" alt="Séréna BAVAROIS" width="75px"> <br> Séréna BAVAROIS | Designer Manager | [Séréna BAVAROIS profile](https://github.com/NanaChocolat)|  [serena.bavarois@algosup.com](mailto:gregory.pagnoux@algosup.com) |

## III. Design

### A. Background

We need a city ruins image in the cartoon design.

<img src="/img/Background1-720x480.jpg" alt="Background 1">
<img src="/img/Background2-720x480.jpg" alt="Background 2">

### B. Characters

**Main**

We need a human character in different posture in the cartoon design :

- doesn't move
- walk right
- walk left
- jump
- punch

**Zombies**

We need a zombie character in different posture in the cartoon design :

- walk right
- walk left
- lying

<img src="/img/zombiesCharacters.jpg" alt="Zombies Characters">

**Bosses**

We need a big zombie character in the cartoon design in unique posture :

- doesn't move

### C. Items

**platforms**

Platforms are long and short planks and metal beam

**teleporters**

Teleporters are blue circles with brown embroidery

## II. Implementation

We have different classes to implement the game :

### A. Characters

- for general characters (main, zombies, bosses)
  - name
  - speed
  - life
  - damage

- for the main character
  - inventory

- for zombies characters
  - name

- for bosses characters
  - name
  - ability

### B. Items

- for platforms
  - name
  - position

- for inventory
  - index
  - name

- for weapons (iron bar, knife, robot, gun)
  - name
  - damage

- for shield
  - defense

- for teleporter
  - index
  - position
