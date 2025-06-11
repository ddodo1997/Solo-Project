<div align="center">
  <h2>🎮 C++ SFML 프로젝트: Arkanoid 모작 🎮</h2>
</div>

---

## 🗂 목차
1. [프로젝트 개요](#프로젝트-개요)
2. [기술 스택](#기술-스택)
3. [구현 요소](#구현-요소)
4. [구현 상세](#구현-상세)
5. [아쉬운 점](#아쉬운-점)
6. [후기](#후기)
   
---

## 프로젝트 개요

- C++과 **SFML**을 활용한 벽돌깨기 게임 **Arkanoid 모작**.
- 첫 개인 게임 프로젝트로, 게임 루프, 충돌 처리, 상태 관리 등 핵심 로직을 직접 설계하고 구현 함.
- 목표는 게임 개발 흐름을 이해하고, json 직렬화 / 역직렬화에 대한 감을 기르는 것.

---

## 기술 스택

<p align="left">
  <img src="https://img.shields.io/badge/C++-00599C?style=flat-square&logo=c%2B%2B&logoColor=white"/>
  <img src="https://img.shields.io/badge/SFML-74C365?style=flat-square&logo=sfml&logoColor=white"/>
  <img src="https://img.shields.io/badge/Visual_Studio-5C2D91?style=flat-square&logo=visual%20studio&logoColor=white"/>
  <img src="https://img.shields.io/badge/Git-F05032?style=flat-square&logo=git&logoColor=white"/>
  <img src="https://img.shields.io/badge/GitHub-181717?style=flat-square&logo=github&logoColor=white"/>
</p>

---

## 구현 요소

| [<img width="200" alt="스크린샷1" src="https://github.com/user-attachments/assets/42048a50-c194-41a3-b193-e850c311e0f2"/>](#공의-반사각) | [<img width="200" alt="스크린샷2" src="https://github.com/user-attachments/assets/e81da18d-7d4f-4036-b744-6fb34536c331"/>](#무한-모드) | [<img width="200" alt="스크린샷3" src="https://github.com/user-attachments/assets/d1abcaf9-90d9-4709-955b-ec24dc1c1c17"/>](#보스전) | [<img width="200" alt="스크린샷4" src="https://github.com/user-attachments/assets/1ebfb02a-2d03-424e-ab08-08629c826224"/>](#보스전) |
|:---:|:---:|:---:|:---:|
| 반사각 | 무한 모드 | 보스전 1 | 보스전 2 |

---

## 구현 상세

1. ### 공의 반사각
   - 공이 패들에 맞는 위치에 따라 반사 각도가 달라지는 물리 처리 구현
   - 벡터 연산을 활용하여 방향 벡터 조정

2. ### 무한 모드
   - 스테이지 종료 없이 점수를 계속 누적하는 Endless Mode 구현
   - 난이도는 시간에 따라 점점 상승

3. ### 보스전
   - 일반 스테이지 모두 클리어 시 보스전 시작
   - 체력/패턴/피격 판정

---

## 아쉬운 점

| 문제 | 해결 방법 |
|------|------------|
| 공이 한 프레임에 여러 벽돌과 충돌할 경우의 처리 | 해당 프레임 내에서 1회 충돌 시, 다른 벽돌과의 충돌을 무시 |
| 스테이지를 추가 하기 위해서는<br> 추가적인 코드 작성이 필요 | 더 나은 구조를 작성하여<br> json파일의 수정만으로 스테이지 추가 / 제거가 손쉽게 이뤄지게 해야함 |

---

## 후기

### 첫 게임 개발 프로젝트로써 일련의 라이프사이클을 이해하는데에 도움이 되었고<br> 충돌, 벡터연산등의 기본 게임 수학의 기조를 이해할 수 있었음.
