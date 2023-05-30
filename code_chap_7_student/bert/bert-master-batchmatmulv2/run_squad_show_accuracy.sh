#!/bin/bash
usage () {
    echo "excution mode:"
    echo "      auto: quantify model and evaluate, choose it for the first time "
    echo "      evaluate: evaluate directly if you have a int model already"
}

if [ $# -lt 1 ]; then
    usage
    exit 1
fi

run_mode=$1
path=$PWD
BERT_BASE_DIR="${AICSE_MODELS_DATA_HOME}/bert/uncased_L-12_H-768_A-12"
CHECKPOINT_DIR="${AICSE_MODELS_MODEL_HOME}/bert/model.ckpt-37000"
SQUAD_DIR="${AICSE_MODELS_DATA_HOME}/bert/squad"
OUTPUT_DIR="./squad_output_dir_128_small"
SQE_LEN=128
BATCH_SIZE=1

echo
echo "=============start run bert==============="
echo

if [ ${run_mode} == "freeze" ] || [ ${run_mode} == "auto" ]; then
  python run_squad.py \
    --vocab_file=${BERT_BASE_DIR}/vocab.txt \
    --bert_config_file=${BERT_BASE_DIR}/bert_config.json \
    --init_checkpoint=${CHECKPOINT_DIR} \
    --export_frozen_graph=true \
    --do_train=false \
    --train_file=${SQUAD_DIR}/train-v1.1.json \
    --do_predict=false \
    --predict_batch_size=${BATCH_SIZE} \
    --predict_file=${SQUAD_DIR}/dev-v1.1.json \
    --train_batch_size=4 \
    --learning_rate=3e-5 \
    --num_train_epochs=2.0 \
    --max_seq_length=${SQE_LEN} \
    --doc_stride=128 \
    --output_dir=${OUTPUT_DIR}
    echo "=============freeze end==============="
fi

if [ ${run_mode} == "quantify" ] || [ ${run_mode} == "auto" ]; then
    echo
    echo "=============quantify begin==============="
    echo
    python fppb_to_intpb.py bert_int16.ini
    echo "=============quantify end==============="
fi

if [ ${run_mode} == "evaluate" ] || [ ${run_mode} == "auto" ]; then
    # evaluate on MLU
    echo
    echo "=============evaluate begin==============="
    echo
    python run_squad.py \
      --vocab_file=${BERT_BASE_DIR}/vocab.txt \
      --bert_config_file=${BERT_BASE_DIR}/bert_config.json \
      --predict_batch_size=${BATCH_SIZE} \
      --max_seq_length=${SQE_LEN} \
      --hidden_size=768 \
      --output_dir=${OUTPUT_DIR} \
      --export_frozen_graph=false \
      --do_predict=true \
      --predict_file=${SQUAD_DIR}/dev-v1.1.json
    python ${SQUAD_DIR}/evaluate-v1.1.py \
        squad/dev-v1.1.json \
        $OUTPUT_DIR/predictions.json 
    echo "=============evaluate end==============="
fi

if [ ${run_mode} == "accuracy" ] || [ ${run_mode} == "auto" ]; then
    echo "=============show accuracy==============="
    python ${SQUAD_DIR}/evaluate-v1.1.py \
        squad/dev-v1.1.json \
        $OUTPUT_DIR/predictions.json
fi
