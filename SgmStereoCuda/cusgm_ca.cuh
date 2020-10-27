/* -*-c++-*- AD-Census - Copyright (C) 2020.
* Author	: Yingsong Li(Ethan Li) <ethan.li.whu@gmail.com>
* Github	: https://github.com/ethan-li-coding
* Describe	: header of class CrossAggregator
*/

#ifndef SGM_CUDA_COST_AGGREGATE_H_
#define SGM_CUDA_COST_AGGREGATE_H_

#include "sgm_types.h"
#include "cusgm_cc.cuh"

class CostAggregator {
public:
	CostAggregator();
	~CostAggregator();

	/**
	 * \brief ��ʼ��
	 * \param width			Ӱ���
	 * \param height		Ӱ���
	 * \param min_disparity ��С�Ӳ�
	 * \param max_disparity ����Ӳ�
	 * \return true: succeed
	 */
	bool Initialize(const sint32& width, const sint32& height, const sint32& min_disparity, const sint32& max_disparity);

	/**\brief Release */
	void Release();

	/**
	 * \brief Ϊ���۾ۺ���������
	 * \param img_left		����ͼ����
	 * \param img_right 	����ͼ����
	 * \param im_psize 		������Ӱ�������ֽڿ�
	 * \param cost_init		��ʼ����
	 */
	void SetData(uint8* img_left, uint8* img_right, const size_t& im_psize, cudaPitchedPtr* cost_init);

	/**
	 * \brief Ϊ���۾ۺ����ò���
	 * \param p1			// p1
	 * \param p2			// p2
	 * \param constant_p2	// �Ƿ���ù̶�p2
	 * \param uniquess		// Ψһ��Լ����ֵ
	 */
	void SetParam(const float32& p1, const float32& p2, const bool& constant_p2, const float32& uniquess);

	/**\brief aggregate */
	void Aggregate(sint16* init_disp_mat = nullptr, const size_t& idp_psize = 0, const StereoROI_T* ste_roi = nullptr);

	/**\brief lr-check */
	void LRCheck(CostComputor* cost_computor, float32 lr_check_thres, sint16* init_disp_mat = nullptr, const size_t& idp_psize = 0, const StereoROI_T* ste_roi = nullptr);


	/** \brief ��ȡ�豸�˾ۺϴ���ָ�� */
	cudaPitchedPtr* get_cost_ptr();

	/** \brief ��ȡ�豸���Ӳ�����ָ�� (����ͼ)*/
	float32* get_disp_ptr() const;

	/** \brief ��ȡ�豸���Ӳ�����ָ�� (����ͼ)*/
	float32* get_disp_r_ptr() const;

	/** \brief ��ȡ�������Ӳ�ͼ�ֽڿ�*/
	size_t get_disp_psize() const;
private:
	/** \brief Ӱ��ߴ� */
	sint32	width_;
	sint32	height_;

	/** \brief Ӱ������ */
	uint8* img_left_;
	uint8* img_right_;
	size_t im_psize_;

	/** \brief �豸���Ӳ�ͼ */
	float32* disp_map_;
	float32* disp_map_r_;
	size_t dp_psize_;

	/** \brief ��ʼ���� */
	cudaPitchedPtr* cost_init_;
	/** \brief �ۺϴ��� */
	cudaPitchedPtr cost_aggr_;
	/** \brief ��ͬ�����ϵľۺϴ��� */
	cudaPitchedPtr cost_aggr_dir_[8];

	/** \brief min_disparity */
	sint32 min_disparity_;
	/** \brief max disparity */
	sint32 max_disparity_;
	/** \brief p1 */
	float32 ca_p1_;
	/** \brief initial p2 */
	float32 ca_p2_;
	/** \brief whether p2 is constant or not */
	bool	constant_p2_;
	/** \brief uniqueness constraint threshold */
	float32 uniquess_;

	/**\brief �豸���첽�� */
	void* cu_streams_;

	/** \brief ��ʼ���ɹ���־ */
	bool is_initialized_;
};

#endif
