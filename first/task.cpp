#include <SFML/Graphics.hpp>
#include <cmath>

// Лимит глубины рекурсии
const int DEPTH_LIMIT = 12;
// Размер базового квадрата
const float BASE_SIZE = 80.f;

// Начальный и конечный цвета для градиента
const sf::Color COLOR_A(205, 92, 92);
const sf::Color COLOR_B(255, 255, 0);

// Поворот двумерного направления
sf::Vector2f rotateVec(const sf::Vector2f& vec, float angleDeg) {
    float rad = angleDeg * static_cast<float>(M_PI) / 180.f;
    float cosA = std::cos(rad);
    float sinA = std::sin(rad);
    return sf::Vector2f(
        vec.x * cosA - vec.y * sinA,
        vec.x * sinA + vec.y * cosA
    );
}

// Получение единичного вектора
sf::Vector2f unitVector(const sf::Vector2f& vec) {
    float len = std::sqrt(vec.x * vec.x + vec.y * vec.y);
    return vec / len;
}

// Линейная интерполяция цвета (градиент)
sf::Color lerpColor(const sf::Color& start, const sf::Color& end, float t) {
    return sf::Color(
        static_cast<sf::Uint8>(start.r + (end.r - start.r) * t),
        static_cast<sf::Uint8>(start.g + (end.g - start.g) * t),
        static_cast<sf::Uint8>(start.b + (end.b - start.b) * t)
    );
}

// Построение фрактала на основе Пифагора
void renderFractal(sf::RenderTarget& canvas, sf::Vector2f baseLeft, sf::Vector2f baseRight, int depth) {
    if (depth > DEPTH_LIMIT)
        return;

    // Квадрат: baseEdge -> основание
    sf::Vector2f baseEdge = baseRight - baseLeft;
    sf::Vector2f perpendicularUp = rotateVec(baseEdge, -90); // перпендикуляр вверх
    sf::Vector2f upperLeft = baseLeft + perpendicularUp;
    sf::Vector2f upperRight = baseRight + perpendicularUp;

    // Цвет по градиенту
    float t = static_cast<float>(depth) / DEPTH_LIMIT;
    sf::Color fillColor = lerpColor(COLOR_A, COLOR_B, t);

    // Отрисовка квадрата
    sf::ConvexShape square;
    square.setPointCount(4);
    square.setPoint(0, baseLeft);
    square.setPoint(1, baseRight);
    square.setPoint(2, upperRight);
    square.setPoint(3, upperLeft);
    square.setFillColor(fillColor);
    canvas.draw(square);

    // Построение треугольника (равнобедренный прямоугольный) вверх
    sf::Vector2f triangleBaseMidpoint = (upperRight + upperLeft) / 2.f;
    sf::Vector2f direction = unitVector(upperRight - upperLeft);
    float baseLength = std::hypot(upperRight.x - upperLeft.x, upperRight.y - upperLeft.y);
    sf::Vector2f triangleHeightVec = rotateVec(direction, -90) * (baseLength / 2.f);
    sf::Vector2f peak = triangleBaseMidpoint + triangleHeightVec; // вверх

    // Прозрачный треугольник (только контур)
    sf::ConvexShape triangle;
    triangle.setPointCount(3);
    triangle.setPoint(0, upperLeft);
    triangle.setPoint(1, upperRight);
    triangle.setPoint(2, peak);
    triangle.setFillColor(sf::Color(0, 0, 0, 0)); // полностью прозрачный
    triangle.setOutlineThickness(1.f);
    triangle.setOutlineColor(sf::Color(50, 50, 50, 100));
    canvas.draw(triangle);

    // Рекурсивно строим новые квадраты на катетах (upperLeft -> peak и peak -> upperRight)
    renderFractal(canvas, upperLeft, peak, depth + 1);
    renderFractal(canvas, peak, upperRight, depth + 1);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pythagoras Tree");
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        // Основание исходного квадрата
        sf::Vector2f baseLeft(400.f - BASE_SIZE / 2.f, 550.f);
        sf::Vector2f baseRight(400.f + BASE_SIZE / 2.f, 550.f);
        renderFractal(window, baseLeft, baseRight, 0);

        window.display();
    }

    return 0;
}

