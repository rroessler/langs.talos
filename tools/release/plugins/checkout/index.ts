/// Package Modules
import { Task } from '../../task';
import { Branch } from '../../product';
import { Context } from '../../context';

/** Checks Out the Required Branch. */
export class Checkout extends Task {
    //  PUBLIC METHODS  //

    /**
     * Sets up the current checkout sequence.
     * @param context               Release context.
     */
    override async setup(context: Context.Readonly) {
        context.spinner.start('Staging Release...');
    }

    /**
     * Handles copying this repository to the desired stage.
     * @param context               Release context.
     */
    override async execute(context: Context.Readonly) {
        // check the current status the be used now
        const status = await context.git.status();

        // check some common assertions that we want now
        if (!context.mock) context.assert.ok(status.isClean(), 'Cannot stage a release from an unclean working tree');
        context.assert.ok(Branch.release(status.current), `Cannot stage a release from '${status.current}' branch`);

        // allow committing any unclean repositories
        await this.m_commit(context, status.isClean());

        // now since we have a clean slate, we want to move this project into the desired repository
        await this.m_stage(context, status.current);

        // once completed, return back to the original branch
        await context.git.checkout(status.current);

        // finally push all the changes as necessary now
        if (!context.mock) await context.git.push(['-u', 'origin']);
    }

    /**
     * Tears down the current checkout sequence.
     * @param context               Release context.
     */
    override async teardown(context: Context.Readonly) {
        context.spinner.succeed('Staged Release Branch');
    }

    //  PRIVATE METHODS  //

    /**
     * Handles committing the current repository.
     * @param context               Release context.
     * @param clean                 Clean repository flag.
     */
    private async m_commit(context: Context.Readonly, clean: boolean) {
        // ignore if the current repository is clean
        if (clean) return;

        // denote that we are committing this release
        context.spinner.text = `Committing '${context.branch}' Changes...`;

        // prepare a suitable message for our commit (always show full-version)
        const message = `Pre-Release v${context.version.build}`;

        // chain our necessary git commands to be used for committing the current changed
        await context.chain([() => context.git.add('.'), () => context.git.commit(message)]);
    }

    /**
     * Handles staging changes to the release branch.
     * @param context               Release context.
     * @param branch                Outgoing branch.
     * @returns
     */
    private async m_stage(context: Context.Readonly, branch: string) {
        // if we are in the same branch, then do nothing
        if (branch === context.branch) return;

        // check if the incoming branch actually exists
        const branches = await context.git.branch();
        const create = !branches.all.includes(context.branch);

        // ensure we checkout the release branch now to merge into
        if (create) await this.m_create(context);

        // always checkout the incoming branch
        await context.git.checkout(context.branch);

        // attempt merging now as necessary
        await context.git.merge([branch]);

        // finally push changes if not in "mock"
        if (!context.mock) await context.git.push(['-u', 'origin']);
    }

    /**
     * Handles creating release branches if necessary.
     * @param context               Release context.
     */
    private async m_create(context: Context.Readonly) {
        await context.git.raw(['branch', '-c', context.branch]);
        await context.git.push(['--set-upstream', 'origin', context.branch]);
        await context.git.push(['-u', 'origin', context.branch]);
    }
}
