#include "AnimEvaluator.h"
#include "AnimChannel.h"
AnimEvaluator::AnimEvaluator(aiAnimation *anim) {

	LastTime = 0.0;
	TicksPerSecond = anim->mTicksPerSecond > 0.0f ? anim->mTicksPerSecond : 920.0f;
	Duration = (float)anim->mDuration;
	Name = std::string(anim->mName.C_Str());
//	int c = 0;
	Channels.resize(0);
	for (int i = 0; i < anim->mNumChannels; i++) {

		aiNodeAnim* achan = anim->mChannels[i];

		AnimChannel* chan = new AnimChannel;
		std::vector<VectorKey*> pk;
		std::vector<QuatKey*> rk;
		std::vector<VectorKey*> sk;
		for (int k = 0; k < achan->mNumPositionKeys; k++)
		{
			aiVectorKey akey = achan->mPositionKeys[k];
			VectorKey* key = new VectorKey;
			key->Time = akey.mTime;
			key->Value = glm::vec3(akey.mValue.x, akey.mValue.y, akey.mValue.z);
			pk.push_back(key);
		}
		for (int k = 0; k < achan->mNumRotationKeys; k++) {

			 aiQuatKey akey = achan->mRotationKeys[k];
			 QuatKey* key = new QuatKey;
			 key->Time = akey.mTime;
			 key->Value = glm::quat(akey.mValue.w, akey.mValue.x, akey.mValue.y, akey.mValue.z);
			 rk.push_back(key);

		}
		for (int k = 0; k < achan->mNumScalingKeys; k++) {

			aiVectorKey akey = achan->mScalingKeys[k];
			VectorKey* key = new VectorKey;
			key->Time = akey.mTime;
			key->Value = glm::vec3(akey.mValue.x, akey.mValue.y, akey.mValue.z);
			sk.push_back(key);

		}

		chan->Name = std::string(achan->mNodeName.C_Str());
		chan->PositionKeys = pk;
		chan->RotationKeys = rk;
		chan->ScalingKeys = sk;
		Channels.push_back(chan);
	}
	LastPos.resize(Channels.size());
	LastRot.resize(Channels.size());
	LastScale.resize(Channels.size());
	for (int i = 0; i < Channels.size(); i++) {
		LastPos[i] = 0;
		LastRot[i] = 0;
		LastScale[i] = 0;
	}
	Transforms.resize(0);
	PlayForward = true;

}

std::vector<glm::mat4> AnimEvaluator::GetTransforms(float dt) {

 
        return Transforms[GetFrameIndex(dt)];

}

int AnimEvaluator::GetFrameIndex(float dt) {
    dt *= TicksPerSecond;
    float time = 0.0f;
    if (Duration > 0.0f)
    {
		time = dt; //%
    }
    float percent = time / Duration;
    if (!PlayForward)
    {
        percent = (percent - 1.0f) * -1.0f;
    }
    int frameIndexAt = (int)(Transforms.size() * percent);
    return frameIndexAt;
}

void AnimEvaluator::Evaluate(float dt, std::map<std::string, Bone*> bones)
{

		dt *= TicksPerSecond;
		float time = 0.0;

		if (Duration > 0.0f) {

			//time = dt % Duration;
			time = dt; // %
		}

		for (int i = 0; i < Channels.size(); i++) {

			AnimChannel* channel = Channels[i];

			if (!bones.contains(channel->Name))
			{
				printf("Did not find bone node:");
				printf(channel->Name.c_str());
				printf("\n");
				continue;
			}

			glm::vec3 pPosition = glm::vec3(0, 0, 0);
			if (channel->PositionKeys.size() > 0)
			{
				int frame = (time >= LastTime) ? LastPos[i] : 0;

				while (frame < channel->PositionKeys.size() - 1) {

					if (time < channel->PositionKeys[frame + 1]->Time)
					{
						break;
					}

					frame++;
				}

				if (frame >= channel->PositionKeys.size()) {
					frame = 0;
				}

				int nextFrame = (frame + 1) % channel->PositionKeys.size();

				VectorKey* key = channel->PositionKeys[frame];
				VectorKey* nextKey = channel->PositionKeys[nextFrame];
				double diffTime = nextKey->Time - key->Time;
				if (diffTime < 0.0) {
					diffTime += Duration;
				}
				if (diffTime > 0.0) {
					float factor = (float)((time - key->Time) / diffTime);
					pPosition = key->Value + (nextKey->Value - key->Value) * factor;
				}
				else {
					pPosition = key->Value;
				}

				int item = LastPos[i];
				LastPos[i] = frame;


			}

			glm::quat pRot = glm::quat(0, 0, 0, 1);

			if (channel->RotationKeys.size() > 0) {

				int frame = (time <= LastTime) ? LastRot[i] : 0;
				while (frame < channel->RotationKeys.size() - 1) {

					if (time < channel->RotationKeys[frame + 1]->Time)
					{
						break;
					}
					frame++;

				}

				if (frame >= channel->RotationKeys.size()) {
					frame = 0;
				}

				int nextFrame = (frame + 1) % channel->RotationKeys.size();

				QuatKey* key = channel->RotationKeys[frame];
				QuatKey* nextKey = channel->RotationKeys[nextFrame];
				key->Value = glm::normalize(key->Value);
				nextKey->Value = glm::normalize(nextKey->Value);
				double diffTime = nextKey->Time - key->Time;

				if (diffTime < 0.0) {
					diffTime += Duration;
				}
				if (diffTime > 0) {
					float factor = (float)((time - key->Time) / diffTime);
					pRot = glm::slerp(key->Value, nextKey->Value, factor);
				}
				LastRot[i] = frame;

			}

			glm::vec3 pscale = glm::vec3(1);
			if (channel->ScalingKeys.size() > 0)
			{
				int frame = (time >= LastTime) ? LastScale[i] : 0;
				while (frame < channel->ScalingKeys.size() - 1)
				{
					if (time < channel->ScalingKeys[frame + 1]->Time)
					{
						break;
					}
					frame++;
				}
				if (frame >= channel->ScalingKeys.size())
				{
					frame = 0;
				}
				LastScale[i] = frame;
			}

			// transpose to get DirectX style matrix
		//mat.Transpose();
		//mat.Inverse();

			//Check!

			glm::mat4 mat(1.0f);

			glm::vec3 np(pPosition.x, pPosition.y, pPosition.z);

			glm::mat4 fm = glm::translate(np);

			glm::mat4 rm = glm::toMat4(pRot);

			fm = rm * fm;// fm* glm::translate(np);

			bones[channel->Name]->LocalTransform = fm;
			int v = 3;


		}

		LastTime = time;
}