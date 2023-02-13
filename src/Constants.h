#pragma once

const float BallRadius = 16.f;
const std::size_t BallPoints = 32;
const float FiringSpeed = 400.0f;
const float PaddleWidth = 10.0f;
const float PaddleHeight = 100.0f;
const float PaddleOffsetFromEdge = 20.0f;
const float PaddleMoveSpeed = 280.0f;
const float AiPaddleMoveSpeed = 420.0f;
const float InitialAiReactionTime = 1.6f;
const float AiReactionTimeStepSize = 0.4f;

enum Side
{
	LEFT = 0,
	RIGHT
};
