/// Node Modules
import * as fs from 'node:fs';
import * as path from 'node:path';
import * as cp from 'node:child_process';

//  PROPERTIES  //

const g_outdir = path.resolve(__dirname); // prepare outputs now
const g_temporary = path.resolve(g_outdir, `callgrind.out.${process.pid}`);
const g_annotated = path.resolve(g_outdir, `callgrind.out.annotated`);
const g_script = path.resolve(process.cwd(), 'examples', 'sandbox.tal');
const g_executable = path.resolve(process.cwd(), 'dist', 'bin', 'talos');

//  TOOL RUNNER  //

(async () => {
    const options: cp.ExecSyncOptions = { cwd: g_outdir, stdio: 'inherit' }; // prepare the incoming command
    const command = `valgrind --tool=callgrind --callgrind-out-file=${g_temporary} ${g_executable} run ${g_script}`;
    const annotate = `callgrind_annotate --tree=both --inclusive=yes --auto=yes --show-percs=yes ${g_temporary} > ${g_annotated}`;

    // attempt running the tool now as necessary in this directory
    await new Promise<void>((resolve) => (cp.execSync(command, options), resolve())).catch(() => {});

    // annotate the output as necessary
    cp.execSync(annotate, options);

    // and visualize this with "qcachegrind"
    cp.execSync(`qcachegrind ${g_temporary}`);
})().finally(() => [g_temporary, g_annotated].forEach((fp) => fs.promises.rm(fp)));
