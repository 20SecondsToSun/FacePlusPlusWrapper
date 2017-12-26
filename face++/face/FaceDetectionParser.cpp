#include "FaceDetectionParser.h"
#include <QJsonArray>

FaceDetectionParcer::FaceDetectionParcer()
{

}

void FaceDetectionParcer::parse(const QJsonObject& jsonObject)
{
    QJsonArray facesJson = jsonObject["faces"].toArray();

    if(facesJson.size() != 0)
    {
        for(int i = 0; i <facesJson.size(); i++)
        {
            Face face;
            QJsonObject faceJson = facesJson[i].toObject();
            face.setToken(faceJson["face_token"].toString());

            //face rectangle
            QJsonObject faceRectangleJson = faceJson["face_rectangle"].toObject();
            FaceRectangle faceRect;           
            faceRect.top    = faceRectangleJson.value("top").toDouble();
            faceRect.left   = faceRectangleJson.value("left").toDouble();
            faceRect.width  = faceRectangleJson.value("width").toDouble();
            faceRect.height = faceRectangleJson.value("height").toDouble();
            face.setFaceRectangle(faceRect);

            // face attributes
            FaceAttributes faceAttributes;

            QJsonObject attributesJson = faceJson["attributes"].toObject();
            QJsonObject headposeJson = attributesJson.value("headpose").toObject();
            faceAttributes.headpose.pitch = headposeJson.value("pitch_angle").toDouble();
            faceAttributes.headpose.roll = headposeJson.value("roll_angle").toDouble();
            faceAttributes.headpose.yaw = headposeJson.value("yaw_angle").toDouble();

            //face eyegaze
            QJsonObject eyegazeJson = attributesJson.value("eyegaze").toObject();

            QJsonObject leftEyegazeJson = eyegazeJson.value("left_eye_gaze").toObject();
            faceAttributes.eyegaze.leftEye.positionXCoordinate
                    = leftEyegazeJson.value("position_x_coordinate").toDouble();
            faceAttributes.eyegaze.leftEye.positionYCoordinate
                    = leftEyegazeJson.value("position_y_coordinate").toDouble();

            QVector3D leftEyeVector;
            leftEyeVector.setX(leftEyegazeJson.value("vector_x_component").toDouble());
            leftEyeVector.setY(leftEyegazeJson.value("vector_y_component").toDouble());
            leftEyeVector.setZ(leftEyegazeJson.value("vector_z_component").toDouble());
            faceAttributes.eyegaze.leftEye.vector = leftEyeVector;

            QJsonObject rightEyegazeJson = eyegazeJson.value("right_eye_gaze").toObject();
            faceAttributes.eyegaze.rightEye.positionXCoordinate
                    = rightEyegazeJson.value("position_x_coordinate").toDouble();
            faceAttributes.eyegaze.rightEye.positionYCoordinate
                    = rightEyegazeJson.value("position_y_coordinate").toDouble();

            QVector3D rightEyeVector;
            rightEyeVector.setX(rightEyegazeJson.value("vector_x_component").toDouble());
            rightEyeVector.setY(rightEyegazeJson.value("vector_y_component").toDouble());
            rightEyeVector.setZ(rightEyegazeJson.value("vector_z_component").toDouble());
            faceAttributes.eyegaze.rightEye.vector = rightEyeVector;

            //gender
            QJsonObject genderJson = attributesJson.value("gender").toObject();
            faceAttributes.gender = genderJson.value("value").toString();

            QJsonObject beautyJson = attributesJson.value("beauty").toObject();
            float maleScore = beautyJson.value("male_score").toDouble();
            float femaleScore = beautyJson.value("female_score").toDouble();

            //landmark
            QJsonObject landmarkJson = faceJson["landmark"].toObject();
            QVector<QPoint> landmarkPoints;
            foreach (const QJsonValue& value, landmarkJson)
            {
                QJsonObject point = value.toObject();
                double x = point.value("x").toDouble();
                double y = point.value("y").toDouble();
                landmarkPoints.push_back(QPoint(x, y));
            }
            face.setLandmark(landmarkPoints);

            //eye left
            faceAttributes.leftEyePosition.setX(landmarkJson["left_eye_center"].toObject().value("x").toDouble());
            faceAttributes.leftEyePosition.setY(landmarkJson["left_eye_center"].toObject().value("y").toDouble());

            //eye right
            faceAttributes.rightEyePosition.setX(landmarkJson["right_eye_center"].toObject().value("x").toDouble());
            faceAttributes.rightEyePosition.setY(landmarkJson["right_eye_center"].toObject().value("y").toDouble());

            faceAttributes.setBeauty(maleScore, femaleScore);

            face.setAttributes(faceAttributes);
            faces.push_back(face);
        }
    }
    else
    {
        //no faces
    }
}

bool FaceDetectionParcer::noFaces() const
{
    return faces.empty();
}

QVector<Face> FaceDetectionParcer::getFaces() const
{
    return faces;
}
